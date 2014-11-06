#ifndef MODEL
#define MODEL

#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct SDrawDesc
{
	unsigned offset;
	unsigned numberOfVertex;
	GLenum mode;

	SDrawDesc() : offset(0), mode(GL_POINT), numberOfVertex(0) { };
	SDrawDesc(unsigned o, unsigned n, GLenum m) : offset(o), mode(m), numberOfVertex(n) { };

	void draw() { glDrawArrays(mode, offset, numberOfVertex); }
};

std::vector<GLfloat> getVertexBufferData(SDrawDesc* frameData, SDrawDesc* fieldData, std::vector<SDrawDesc>& signData);
std::vector<glm::vec3> getColors();

#endif
