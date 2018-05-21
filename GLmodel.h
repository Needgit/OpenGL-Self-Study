#ifndef GLMODEL_H_
#define GLMODEL_H_

#include "GLmesh.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <stb/stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <sstream>
#include <string>
#include <vector>


class GLmodel
{
public:
    void Draw(GLshader shader);

	GLmodel(const GLchar* path)
    {
        loadModel(path);
    }
	GLmodel() {};
	virtual ~GLmodel();

private:
	std::vector<GLmesh::Texture> textures_loaded;
    std::vector<GLmesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    GLmesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<GLmesh::Texture> loadMaterialTextures(
    		aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif /* GLMODEL_H_ */
