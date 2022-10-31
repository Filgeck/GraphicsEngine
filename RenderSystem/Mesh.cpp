//
// Created by Filipp Kondrashov on 06/07/2022.
//

#include "Mesh.h"

//remove
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures)
{
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    VAO.Bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::Draw(Shader &shader, Camera &camera, glm::mat4 parentMatrix)
{
    shader.Activate();
    VAO.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string num;
        std::string type = textures[i].type;
        if(type == "diffuse")
        {
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        textures[i].texUnit(shader, (type+num).c_str(), i);
        textures[i].Bind();
    }
    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    trans = glm::translate(trans, position);
    glm::quat r = glm::quat(rotation);
    rot = glm::mat4_cast(r);
    sca = glm::scale(sca, scale);

    matrix = parentMatrix*(trans*rot*sca);
    //matrix = trans*rot*sca;

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
{
    position = pos;
    rotation = rot;
    scale = sca;
}

void Mesh::translate(glm::vec3 dir)
{
    position.x += dir.x;
    position.y +=dir.y;
    position.z += dir.z;
}

void Mesh::rotate(glm::vec3 dir)
{
    rotation.x += dir.x;
    rotation.y +=dir.y;
    rotation.z += dir.z;
}
