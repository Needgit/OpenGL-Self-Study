#include "GLcamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLcamera::GLcamera()
{
	shader = NULL;
}

float GLcamera::clampAngle(float angle)
{
	if (angle >= 360.0f)
		angle -= 360.0f;
	else
	if (angle < 0.0f)
		angle += 360.0f;

	return angle;
}


void GLcamera::setPosition(glm::vec3 position)
{
	this->position = position;
}


void GLcamera::setRotation(glm::vec3 rotation)
{
	this->rotation.x = clampAngle(rotation.x);
	this->rotation.y = clampAngle(rotation.y);
	this->rotation.z = clampAngle(rotation.z);
}


GLcamera::GLcamera(GLshader &shader, glm::vec3 position, glm::vec3 rotation)
{
	this->shader = &shader;

	setPosition(position);
	setRotation(rotation);
}

GLcamera::~GLcamera()
{
	// Empty
}


void GLcamera::setShader(GLshader &shader)
{
	this->shader = &shader;
}


void GLcamera::update()
{
	glm::mat4 view;
	view = glm::translate(view, this->position);
	view = glm::rotate(view, glm::radians(this->rotation.x), glm::vec3(1, 0, 0));
	view = glm::rotate(view, glm::radians(this->rotation.y), glm::vec3(0, 1, 0));
	view = glm::rotate(view, glm::radians(this->rotation.z), glm::vec3(0, 0, 1));

	shader->setMat4("view", view);
}
