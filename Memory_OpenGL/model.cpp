#include "model.h"

std::vector<GLfloat> getVertexBufferData(SDrawDesc* frameData, SDrawDesc* fieldData, std::vector<SDrawDesc>& signData)
{
	unsigned offset = 0;

	std::vector<GLfloat> vertexBufferData{
		-1.f, 1.f,
		1.f, 1.f,
		1.f, -1.f,
		-1.f, -1.f,
		-1.f, 1.f
	};
	*frameData = SDrawDesc(offset, vertexBufferData.size()/2, GL_LINE_STRIP);
	offset = vertexBufferData.size() / 2;

	std::vector<GLfloat> field{
		-1.f, 1.f,
		1.f, 1.f,
		-1.f, -1.f,
		1.f, -1.f,
	};
	vertexBufferData.insert(vertexBufferData.end(), field.begin(), field.end());
	*fieldData = SDrawDesc(offset, field.size()/2, GL_TRIANGLE_STRIP);
	offset = vertexBufferData.size() / 2;

	std::vector<GLfloat> shape1{
		0.f, 1.f,
		-1.f, -1.f,
		1.f, -1.f
	};
	vertexBufferData.insert(vertexBufferData.end(), shape1.begin(), shape1.end());
	signData.push_back(SDrawDesc(offset, shape1.size()/2, GL_TRIANGLES));
	offset = vertexBufferData.size() / 2;


	std::vector<GLfloat> shape2{
		-1.f, 1.f,
		1.f, 1.f,
		-1.f, -1.f,
		1.f, -1.f
	};
	vertexBufferData.insert(vertexBufferData.end(), shape2.begin(), shape2.end());
	signData.push_back(SDrawDesc(offset, shape2.size() / 2, GL_TRIANGLE_STRIP));
	offset = vertexBufferData.size() / 2;

	std::vector<GLfloat> shape3{
		0.f, 1.f,
		1.f, 0.f,
		-1.f, 0.f,
		0.f, -1.f
	};
	vertexBufferData.insert(vertexBufferData.end(), shape3.begin(), shape3.end());
	signData.push_back(SDrawDesc(offset, shape3.size() / 2, GL_TRIANGLE_STRIP));
	offset = vertexBufferData.size() / 2;

	std::vector<GLfloat> shape4{
		0.f, 0.f,
		1.f, 0.f,
		0.5f, 1.f,
		-0.5f, 1.f,
		-1.f, 0.f,
		-0.5f, -1.f,
		0.5f, -1.f,
		1.f, 0.f
	};
	vertexBufferData.insert(vertexBufferData.end(), shape4.begin(), shape4.end());
	signData.push_back(SDrawDesc(offset, shape4.size() / 2, GL_TRIANGLE_FAN));
	offset = vertexBufferData.size() / 2;

	std::vector<GLfloat> shape5{
		-1.f, -1.f,
		-0.5f, 1.f,
		0.5f, -1.f,
		1.f, 1.f
	};
	vertexBufferData.insert(vertexBufferData.end(), shape5.begin(), shape5.end());
	signData.push_back(SDrawDesc(offset, shape5.size() / 2, GL_TRIANGLE_STRIP));
	offset = vertexBufferData.size() / 2;

	std::vector<GLfloat> shape6{
		-1.f, 1.f,
		1.f, 1.f,
		0.f, -1.f
	};
	vertexBufferData.insert(vertexBufferData.end(), shape6.begin(), shape6.end());
	signData.push_back(SDrawDesc(offset, shape6.size() / 2, GL_TRIANGLES));
	offset = vertexBufferData.size() / 2;

	std::vector<GLfloat> shape7{
		-1.f, -1.f,
		-0.5f, 1.f,
		1.f, -1.f,
		0.5f, 1.f
	};
	vertexBufferData.insert(vertexBufferData.end(), shape7.begin(), shape7.end());
	signData.push_back(SDrawDesc(offset, shape7.size() / 2, GL_TRIANGLE_STRIP));
	offset = vertexBufferData.size() / 2;

	std::vector<GLfloat> shape8{
		-1.f, 1.f,
		1.f, 1.f,
		0.f, -0.5f,
		0.f, 0.5f,
		-1.f, -1.f,
		1.f, -1.f
	};
	vertexBufferData.insert(vertexBufferData.end(), shape8.begin(), shape8.end());
	signData.push_back(SDrawDesc(offset, shape8.size() / 2, GL_TRIANGLES));
	offset = vertexBufferData.size() / 2;

	return vertexBufferData;
};

std::vector<glm::vec3> getColors()
{
	return std::vector<glm::vec3>{
		glm::vec3(1.f, 0.f, 0.f), // select frame color
		glm::vec3(1.0f, 0.5f, 0.f), //	front color
		glm::vec3(0.3f, 0.3f, 0.3f), //	background sign color
		glm::vec3(0.0f, 0.f, 0.f),	//	sign color...
		glm::vec3(1.0f, 0.f, 0.f),
		glm::vec3(1.0f, 1.f, 0.f),
		glm::vec3(0.0f, 1.f, 0.f),
		glm::vec3(0.0f, 1.f, 1.f),
		glm::vec3(0.0f, 0.f, 1.f),
		glm::vec3(1.0f, 0.f, 1.f),
		glm::vec3(1.0f, 1.f, 1.f)
	};
};