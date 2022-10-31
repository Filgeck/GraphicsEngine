//
// Created by Filipp Kondrashov on 06/07/2022.
//

#include "Model.h"

Model::Model(const char* path)
{
    loadModel(path);
}

void Model::Draw(Shader &shader, Camera &camera, glm::mat4 componentMatrix) {
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader, camera, componentMatrix);
}

void Model::loadModel(std::string path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
// process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Mesh newMesh = processMesh(mesh, scene);
        aiVector3t<float> pos;
        aiVector3t<float> rot;
        aiVector3t<float> sca;
        node->mTransformation.Decompose(sca, rot, pos);
        newMesh.setTransform(glm::vec3(pos.x, pos.y, pos.z), glm::vec3(rot.x, rot.y, rot.z), glm::vec3(sca.x, sca.y, sca.z));
        meshes.push_back(newMesh);
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    // walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texUV = vec;
        }
        else
            vertex.texUV = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }


    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    // return a mesh object created from the extracted mesh data


    //textures.push_back(Texture("backpack/diffuse.jpg", "diffuse", 0, GL_UNSIGNED_BYTE));
    //textures.push_back(Texture("Textures/planksSpec.png", "specular", 1, GL_UNSIGNED_BYTE));

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;
    std::cout << std::endl << typeName << std::endl;
    std::cout << "number of loaded textures: " << textures_loaded.size() << std::endl;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        std::string dir;
        std::cout << "found texture: " << str.C_Str() << std::endl;
        for(auto & j : textures_loaded)
        {
            dir = directory + '/' + str.C_Str();
            std::cout << "comparing existing texture: " << j.path << " with our texture: " << dir.c_str() << std::endl;
            if(std::strcmp(j.path, dir.c_str()) == 0)
            {
                std::cout << "texture was already loaded, " << std::endl;
                textures.push_back(j);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            std::cout << "trying to load a new texture " << std::endl;
            dir = directory + '/' + str.C_Str();
            textures_loaded.push_back(Texture(dir.c_str(), typeName.c_str(), textures_loaded.size(), GL_UNSIGNED_BYTE));
        }
    }
    return textures;
}

void Model::translate(glm::vec3 dir)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].translate(dir);
}

void Model::rotate(glm::vec3 dir)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].rotate(dir);
}
