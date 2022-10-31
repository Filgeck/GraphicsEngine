//
// Created by Filipp Kondrashov on 05/07/2022.
//

#ifndef GRAPHICSENGINE_TEXTURE_H
#define GRAPHICSENGINE_TEXTURE_H

#include <glad/glad.h>
#include "stb/stb_image.h"
#include "Shader.h"

class Texture{
public:
    GLuint ID;
    const char* type;
    GLuint unit;
    const char* path;
    GLenum format;

    Texture(const char* image, const char* texType, GLuint slot, GLenum pixelType);

    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};


#endif //GRAPHICSENGINE_TEXTURE_H
