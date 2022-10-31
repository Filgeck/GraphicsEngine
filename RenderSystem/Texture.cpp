//
// Created by Filipp Kondrashov on 05/07/2022.
//

#include "Texture.h"

Texture::Texture(const char *image, const char* texType, GLuint slot, GLenum pixelType)
{
    path = strdup(image);
    type = strdup(texType);
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    std::cout << "Loading texture " << path << std::endl;
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
    if (bytes)
    {
        glGenTextures(1, &ID);
        glActiveTexture(GL_TEXTURE0 + slot);
        unit = slot;

        if (numColCh == 1)
        {
            format = GL_RED;
        }
        else if (numColCh == 3)
            format = GL_RGB;
        else if (numColCh == 4)
            format = GL_RGBA;


        glBindTexture(GL_TEXTURE_2D, ID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(bytes);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(bytes);
    }

}

void Texture::texUnit(Shader& shader, const char *uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &ID);
}
