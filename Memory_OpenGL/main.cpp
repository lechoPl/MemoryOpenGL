#include <cstdlib>
#include <cstdio>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <vector>

#include "shader.hpp"
#include "memoryGame.h"
#include "model.h"
#include "field.h"

using namespace std;

CMemoryGame g_game;


static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (!g_game.isWin() && (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN ||
		key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT) && action == GLFW_PRESS)
	{
		g_game.movePos(static_cast<KEY>(key));
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		g_game.selectField();
	}

}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Memmory Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		return -1;
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("VertexShader.vshader", "FragmentShader.fshader");

	GLuint ColorID = glGetUniformLocation(programID, "colorData");
	GLuint PositionID = glGetUniformLocation(programID, "position");
	GLuint ScaleID = glGetUniformLocation(programID, "scale");
	GLuint AnimationXID = glGetUniformLocation(programID, "animationX");

	SDrawDesc frameData;
	SDrawDesc fieldData;
	std::vector<SDrawDesc> signData;
	std::vector<glm::vec3> colorData = getColors();
	vector<GLfloat> vertex_data = getVertexBufferData(&frameData, &fieldData, signData);
	
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_data.size()*sizeof(GLfloat), &vertex_data[0], GL_STATIC_DRAW);

	GLfloat posX;
	GLfloat posY;
	int fieldTypeId;
	unsigned fieldBgColorId;
	CField* tempField;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Use shader
		glUseProgram(programID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		
		if (!g_game.isWin()) {

			posX = -1.f + 0.25f + 0.5f * g_game.getCurrentPos().x;
			posY = 1.f - 0.25f - 0.5f * g_game.getCurrentPos().y;
			glUniform3f(ColorID, colorData.at(0).x, colorData.at(0).y, colorData.at(0).z);
			glUniform2f(PositionID, posX, posY);
			glUniform1f(ScaleID, 0.24f);
			glUniform1f(AnimationXID, 1.f);
			frameData.draw();

			for (unsigned x = 0; x < g_game.getSize(); ++x)
			{
				for (unsigned y = 0; y < g_game.getSize(); ++y)
				{
					tempField = g_game.getField(x, y);
					fieldTypeId = tempField->getTypeId();

					if (fieldTypeId < 0)
						continue;

					posX = -1.f + 0.25f + 0.5f * x;
					posY = 1.f - 0.25f - 0.5f * y;
					glUniform2f(PositionID, posX, posY);

					if (!tempField->isAnimationStarted())
					{
						glUniform1f(AnimationXID, 1.f);

						fieldBgColorId = tempField->isSignVisable() ? 2 : 1;
						glUniform3f(ColorID, colorData.at(fieldBgColorId).x, colorData.at(fieldBgColorId).y, colorData.at(fieldBgColorId).z);
						glUniform1f(ScaleID, 0.23f);
						fieldData.draw();

						if (tempField->isSignVisable())
						{
							glUniform3f(ColorID, colorData.at(fieldTypeId + 3).x, colorData.at(fieldTypeId + 3).y, colorData.at(fieldTypeId + 3).z);
							glUniform1f(ScaleID, 0.20f);

							signData.at(fieldTypeId).draw();
						}
					}
					else
					{
						float animationX = cos(glm::pi<double>() * tempField->getAnimationTime());
						glUniform1f(AnimationXID, abs(animationX));

						bool showSign = animationX < 0 ? !tempField->isHideAnimation() : tempField->isHideAnimation();
						
						fieldBgColorId = showSign ? 2 : 1;
						glUniform3f(ColorID, colorData.at(fieldBgColorId).x, colorData.at(fieldBgColorId).y, colorData.at(fieldBgColorId).z);
						glUniform1f(ScaleID, 0.23f);
						fieldData.draw();

						if (showSign)
						{
							glUniform3f(ColorID, colorData.at(fieldTypeId + 3).x, colorData.at(fieldTypeId + 3).y, colorData.at(fieldTypeId + 3).z);
							glUniform1f(ScaleID, 0.20f);

							signData.at(fieldTypeId).draw();
						}
					}

				}
			}
		}

		glDisableVertexAttribArray(0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();
	return 0;
}