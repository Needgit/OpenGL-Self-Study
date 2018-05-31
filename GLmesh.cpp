/*
 * GLmesh.cpp
 *
 *  Created on: May 18, 2018
 *      Author: stalkie
 */

#include "GLmesh.h"

GLmesh::GLmesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices  = indices;
    this->textures = textures;

    setupMesh();
}


GLmesh::~GLmesh()
{

}


void GLmesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

	// We want to use the VAO:
	glBindVertexArray(VAO);

    // Bind VBO and copy verticies data into buffer:
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// Set vertex attribute (layout (location = 0) in vec3 position).:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Set vertex attribute (layout (location = 1) in vec3 normal)...:
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // Set vertex attribute (layout (location = 2) in vec2 texCoords):
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

template <typename T>
std::string NumberToString ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}


void GLmesh::Draw(GLshader shader)
{
	GLuint diffuseNr  = 0;
	GLuint specularNr = 0;
    for(GLuint i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "diffuse")
            number = NumberToString<GLuint>(diffuseNr++);
        else if(name == "specular")
            number = NumberToString<GLuint>(specularNr++);

        shader.setFloat(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // Draw the Mesh:
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);
}
