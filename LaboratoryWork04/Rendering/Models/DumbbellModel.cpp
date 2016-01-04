#include "DumbbellModel.h"

using namespace Engine::Rendering::Models;
using namespace Engine::Rendering;

DumbbellModel::DumbbellModel() :
	DumbbellModel(glm::vec3(0.0f, 0.0f, 0.0f), DEFAULT_DUMBBELL_RADIUS, DEFAULT_SPHERE_WIDTH, DEFAULT_DUMBBELL_LENGTH, DEFAULT_DUMBBELL_SMOOTHNESS)
{
}

DumbbellModel::DumbbellModel(float radius, float sphereWid, float dubbLen) :
	DumbbellModel(glm::vec3(0.0, 0.0, 0.0), radius, sphereWid, dubbLen, DEFAULT_DUMBBELL_SMOOTHNESS)
{
}

DumbbellModel::DumbbellModel(float radius, float sphereWid, float dubbLen, unsigned int smooth) :
	DumbbellModel(glm::vec3(0.0, 0.0, 0.0), radius, sphereWid, dubbLen, smooth)
{
}

DumbbellModel::DumbbellModel(glm::vec3 position, float rad, float sphereWid, float dubbLen, unsigned int smooth) :
	radius(rad), sphereWidth(sphereWid), dumbbellLength(dubbLen), smoothness(smooth)
{
	this->position = position;
	angle = 0;
	cameraRotation = glm::vec3(0, 0, 0);
	cameraPosition = glm::vec3(0, 0, 0);
}



DumbbellModel::~DumbbellModel()
{
}

void DumbbellModel::create()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;

	float totalLength = 2 * sphereWidth + dumbbellLength;
	float spheresInterval = totalLength - 4 * radius;

	unsigned int vertexCounter = 0;
	float dumbbellRadius = sqrt(sphereWidth*(2 * radius - sphereWidth));
	for (unsigned int iCounter = 0; iCounter < 360; iCounter += 360 / smoothness)
	{
		if (spheresInterval / 2 + radius - sin(iCounter * M_PI / 180) * radius < dumbbellLength / 2)
			continue;
		for (unsigned int jCounter = 0; jCounter < 360; jCounter += 360 / smoothness)
		{
			vertices.push_back(VertexFormat(
				glm::vec3(sin(iCounter * M_PI / 180) * radius - spheresInterval / 2 - radius,
					cos(iCounter * M_PI / 180) * sin(jCounter * M_PI / 180) * radius,
					cos(iCounter * M_PI / 180) * cos(jCounter * M_PI / 180) * radius),
				glm::vec4(1.0, 1.0, 1.0, 1.0)));
			vertexCounter++;
		}
	}
	for (float iCounter = 0; iCounter < dumbbellLength; iCounter += dumbbellLength / smoothness)
	{
		for (unsigned int jCounter = 0; jCounter < 360; jCounter += 360 / smoothness)
		{
			vertices.push_back(VertexFormat(
				glm::vec3(iCounter - dumbbellLength / 2,
					sin(jCounter * M_PI / 180) * dumbbellRadius,
					cos(jCounter * M_PI / 180) * dumbbellRadius),
				glm::vec4(1.0, 1.0, 1.0, 1.0)));
			vertexCounter++;
		}
	}
	for (unsigned int iCounter = 0; iCounter < 360; iCounter += 360 / smoothness)
	{
		if (sin(iCounter * M_PI / 180) * radius + spheresInterval / 2 + radius < dumbbellLength / 2)
			continue;
		for (unsigned int jCounter = 0; jCounter < 360; jCounter += 360 / smoothness)
		{
			vertices.push_back(VertexFormat(
				glm::vec3(sin(iCounter * M_PI / 180) * radius + spheresInterval / 2 + radius,
					cos(iCounter * M_PI / 180) * sin(jCounter * M_PI / 180) * radius,
					cos(iCounter * M_PI / 180) * cos(jCounter * M_PI / 180) * radius),
				glm::vec4(1.0, 1.0, 1.0, 1.0)));
			vertexCounter++;
		}
	}


	vertexCount = vertexCounter;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertexCount, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
}

void DumbbellModel::draw(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix)
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glUniform3f(glGetUniformLocation(program, "position"),
		position.x,
		position.y,
		position.z);
	glUniform3f(glGetUniformLocation(program, "camera_position"),
		cameraPosition.x,
		cameraPosition.y,
		cameraPosition.z);
	glUniform3f(glGetUniformLocation(program, "camera_rotation"),
		cameraRotation.x,
		cameraRotation.y,
		cameraRotation.z);
	glUniform3f(glGetUniformLocation(program, "rotation"),
		0.0f,
		angle * M_PI / 180,
		0.0f);


	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1,
		false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projectionMatrix[0][0]);

	glDrawArrays(GL_LINE_STRIP, 0, vertexCount);
}

void DumbbellModel::update()
{
	angle += 0.2f;
}
