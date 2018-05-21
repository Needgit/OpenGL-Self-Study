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
	GLshader* shader;

	glm::vec3 position;
	glm::vec3 rotation;

	GLuint window_width;
	GLuint window_height;


	float clampAngle(float angle);

public:
	GLcamera();
	GLcamera(GLshader &shader, glm::vec3 position, glm::vec3 rotation);
	virtual ~GLcamera();


	void setShader(GLshader &shader);
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);

	void setWindowSize(GLint width, GLint height);

	void update();
};

#endif /* GLCAMERA_H_ */
