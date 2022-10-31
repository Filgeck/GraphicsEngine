//
// Created by Filipp Kondrashov on 05/07/2022.
//

#ifndef GRAPHICSENGINE_EBO_H
#define GRAPHICSENGINE_EBO_H

#include <vector>
#include <glad/glad.h>

class EBO {
public:
    GLuint ID;
    EBO(std::vector<GLuint>& indices);

    void Bind();
    void Unbind();
    void Delete();
};


#endif //GRAPHICSENGINE_EBO_H
