#ifndef GLCAMERA_H_
#define GLCAMERA_H_

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLshader.h"

class GLcamera
{
private:
	GLuint window_width;
	GLuint window_height;


	float clampAngle(float angle);

public:
	glm::vec3 position;
	glm::vec3 rotation;

	GLcamera();
	GLcamera(glm::vec3 position, glm::vec3 rotation);
	virtual ~GLcamera();

	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);

	void setWindowSize(GLint width, GLint height);

	void update(GLshader shader);
};

#endif /* GLCAMERA_H_ */
