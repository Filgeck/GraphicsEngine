//
// Created by Filipp Kondrashov on 06/07/2022.
//

#ifndef GRAPHICSENGINE_MESH_H
#define GRAPHICSENGINE_MESH_H

#include<string>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Mesh {
public:
    std::vector <Vertex> vertices;
    std::vector <GLuint> indices;
    std::vector <Texture> textures;

    Mesh* parent;
    glm::mat4 matrix = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(-1.0f, 1.0f, 1.0f);

    VAO VAO;

    Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

    void Draw(Shader& shader, Camera& camera, glm::mat4 parentMatrix);
    void setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca);
    void translate(glm::vec3 dir);
    void rotate(glm::vec3 dir);
};


#endif //GRAPHICSENGINE_MESH_H
