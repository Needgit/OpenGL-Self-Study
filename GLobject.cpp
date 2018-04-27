#include "GLobject.h"

struct Vertex
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

Vertex verticies[] =
{
		{ 1.000000, -1.000000, -1.000000},
		{ 1.000000, -1.000000,  1.000000},
		{-1.000000, -1.000000,  1.000000},
		{-1.000000, -1.000000, -1.000000},
		{ 1.000000,  1.000000, -1.000000},
		{ 1.000000,  1.000000,  1.000000},
		{-1.000000,  1.000000,  1.000000},
		{-1.000000,  1.000000, -1.000000}
};


GLobject::GLobject()
{
	this->vao    = 0;
	this->buffer = 0;
}

GLobject::GLobject(std::string filePath)
{
	glCreateVertexArrays(1, &this->vao);

	// Create buffers:
	glCreateBuffers(1,  &this->buffer);
	glNamedBufferStorage(this->buffer, sizeof(verticies), verticies, 0);

	glVertexArrayAttribBinding(this->vao, 0, 0);
	glVertexArrayAttribFormat( this->vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, x));
	glEnableVertexArrayAttrib(this->vao, 0);

	glVertexArrayVertexBuffer(this->vao, 0, this->buffer, 0, sizeof(GLfloat));
}


GLobject::~GLobject()
{
	// TODO Auto-generated destructor stub
}


void GLobject::drawObject()
{
	glDrawArrays(GL_POINTS, this->vao, 1);
}
