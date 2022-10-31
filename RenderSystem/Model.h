//
// Created by Filipp Kondrashov on 06/07/2022.
//

#ifndef GRAPHICSENGINE_MODEL_H
#define GRAPHICSENGINE_MODEL_H

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "VBO.h"

class Model {
    public:
        Model(const char* path);
        void Draw(Shader &shader,  Camera &camera, glm::mat4 componentMatrix);
        void translate(glm::vec3 dir);
        void rotate(glm::vec3 dir);
        std::vector<Mesh> meshes;
        std::vector<glm::vec3> translationsMeshes;

    private:
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        // model data
        std::vector<Texture> textures_loaded;
        std::string directory;
};


#endif //GRAPHICSENGINE_MODEL_H
