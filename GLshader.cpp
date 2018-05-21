#include "GLshader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


GLshader::GLshader()
{
	this->ID = 0;
}


GLuint GLshader::compileShader(GLenum gl_shader, std::string source)
{
	GLuint shader;

	GLint  success;
	GLchar infoLog[512];

	const GLchar* source_c = source.c_str();

	// Create and compile vertex shader:
	shader = glCreateShader(gl_shader);
	glShaderSource(shader, 1, &source_c, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	    std::cout << source_c << std::endl;
	}

	return shader;
}

GLshader::GLshader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	GLuint vShader, fShader;

	GLint  success;
	GLchar infoLog[512];

	std::string vertex_shader_source, fragment_shader_source;

    std::ifstream vShaderFile, fShaderFile;
    // Ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertex_shader_source   = vShaderStream.str();
		fragment_shader_source = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	// Create and compile vertex shader:
    vShader = compileShader(GL_VERTEX_SHADER, vertex_shader_source);

	// Create and compile fragment shader:
    fShader = compileShader(GL_FRAGMENT_SHADER, fragment_shader_source);

	// Create program and linking:
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vShader);
	glAttachShader(this->ID, fShader);
	glLinkProgram(this->ID);

//	std::cout << "this->ID " << this->ID << std::endl;

	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if(!success)
	{
	    glGetProgramInfoLog(ID, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Clean up:
	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

GLshader::~GLshader()
{
	// Empty;
}


void GLshader::use()
{
	glUseProgram(this->ID);
}


void GLshader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}


void GLshader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}


void GLshader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void GLshader::setMat4(const std::string &name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

