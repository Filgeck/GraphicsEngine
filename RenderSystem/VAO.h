//
// Created by Filipp Kondrashov on 05/07/2022.
//

#ifndef GRAPHICSENGINE_VAO_H
#define GRAPHICSENGINE_VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
};


#endif //GRAPHICSENGINE_VAO_H
