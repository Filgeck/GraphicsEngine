//
// Created by Filipp Kondrashov on 08/07/2022.
//

#ifndef GRAPHICSENGINE_RENDERINGSYSTEM_H
#define GRAPHICSENGINE_RENDERINGSYSTEM_H

//#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include "VBO.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Model.h"
#include "iostream"

class RenderingSystem
{
public:

    static RenderingSystem& getInstance()
    {
        static RenderingSystem    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    RenderingSystem(RenderingSystem const&)  = delete;
    void operator=(RenderingSystem const&)  = delete;

    Shader& getDefaultShader()
    {
        return defaultShader;
    }
    Shader& getLightShader()
    {
        return lightShader;
    }
    Shader& getOutlineShader()
    {
        return outlineProgram;
    }
    Camera& getCamera()
    {
        return camera;
    }
    GLFWwindow* getWindow()
    {
        return window;
    }
    void setWindow(GLFWwindow* win)
    {
        window = win;
    }
private:
    RenderingSystem()
            : camera(800, 800, glm::vec3(0.0f, 0.0f, 2.0f)),
              defaultShader("Shaders/default.vert", "Shaders/default.frag"),
              lightShader("Shaders/light.vert", "Shaders/light.frag"),
              outlineProgram("Shaders/outline.vert", "Shaders/outline.frag")
    {
        //glfwSetErrorCallback( error_callback );

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glDepthFunc(GL_LESS);
    };

    const unsigned int width = 800;
    const unsigned int height = 800;

    GLFWwindow* window;
    Camera camera;
    Shader defaultShader;
    Shader lightShader;
    Shader outlineProgram;
};

#endif //GRAPHICSENGINE_RENDERINGSYSTEM_H
