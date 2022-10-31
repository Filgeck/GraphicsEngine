//
// Created by Filipp Kondrashov on 05/07/2022.
//

#ifndef GRAPHICSENGINE_SHADER_H
#define GRAPHICSENGINE_SHADER_H

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const std::string& path);

class Shader {
public:
    GLuint ID;
    Shader(const std::string& vertexFile, const std::string& fragmentFile);

    void Activate();
    void Delete();
private:
    void compileErrors(unsigned int shader, const char* type);
};


#endif //GRAPHICSENGINE_SHADER_H
