#ifndef GLSHADER_H_
#define GLSHADER_H_


#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class GLshader
{
private:
	GLuint compileShader(GLenum gl_shader, std::string source);


public:
    GLuint ID;

    GLshader();
    GLshader(const GLchar* vertexPath, const GLchar* fragmentPath);
	virtual ~GLshader();

    void use();

    void setAmbience (glm::vec3 value) const;
    void setDiffuse  (glm::vec3 value) const;
    void setSpecular (glm::vec3 value) const;
    void setShininess(GLubyte value)   const;

    void setBool (const std::string &name, bool      value) const;
    void setInt  (const std::string &name, int       value) const;
    void setFloat(const std::string &name, float     value) const;
    void setVec3 (const std::string &name, glm::vec3 value) const;

    void setMat4 (const std::string &name, glm::mat4 value) const;
};

#endif /* GLSHADER_H_ */
