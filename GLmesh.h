#ifndef GLMESH_H_
#define GLMESH_H_


#include "GLshader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <sstream>
#include <string>
#include <vector>


class GLmesh
{
public:
	struct Vertex
	{
	    glm::vec3 position;
	    glm::vec3 normal;
	    glm::vec2 texCoords;
	};

	struct Texture
	{
		GLuint id;
	    std::string type;
	    std::string path;  // we store the path of the texture to compare with other textures
	};

	GLuint VAO, VBO, EBO;

	GLmesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	virtual ~GLmesh();

	void Draw(GLshader shader);

private:
	std::vector<Vertex>  vertices;
	std::vector<GLuint>  indices;
	std::vector<Texture> textures;

    void setupMesh();

};

#endif /* GLMESH_H_ */
