#ifndef GLOBJECT_H_
#define GLOBJECT_H_

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

class GLobject
{
private:
	GLuint vao;
	GLuint buffer;

public:
	GLobject();
	GLobject(std::string filePath);
	virtual ~GLobject();

	void drawObject();
};

#endif /* GLOBJECT_H_ */
