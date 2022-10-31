#include <iostream>
#include "RenderSystem/Mesh.h"
#include "RenderSystem/Model.h"
#include "RenderSystem/RenderingSystem.h"
#include "Core/Scene.h"
#include "Core/MeshComponent.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{

    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    int w;
    int h;
    glfwGetFramebufferSize(window, &w, &h); //mac specific
    glViewport(0, 0,  w, h);

    RenderingSystem& renderingSystem = RenderingSystem::getInstance();
    renderingSystem.setWindow(window);



    Vertex lightVertices[] =
            { //     COORDINATES     //
                    Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
                    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
                    Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
                    Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
                    Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
                    Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
                    Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
                    Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
            };

    GLuint lightIndices[] =
            {
                0, 1, 2,
                0, 2, 3,
                0, 4, 7,
                0, 7, 3,
                3, 7, 6,
                3, 6, 2,
                2, 6, 5,
                2, 5, 1,
                1, 5, 4,
                1, 4, 0,
                4, 5, 6,
                4, 6, 7
            };

    std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    std::vector <Texture> tex;
    Mesh light(lightVerts, lightInd, tex);

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(2.0f, 2.0f, 2.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    light.translate(lightPos);

    renderingSystem.getLightShader().Activate();
    glUniformMatrix4fv(glGetUniformLocation(renderingSystem.getLightShader().ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(renderingSystem.getLightShader().ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    renderingSystem.getDefaultShader().Activate();
    glUniform4f(glGetUniformLocation(renderingSystem.getDefaultShader().ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(renderingSystem.getDefaultShader().ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    Scene mainScene = Scene();
    GameObject* backpackGameObject = mainScene.addGameObjectToScene("backpack");
    MeshComponent backpackMesh = MeshComponent("backpack/backpack.obj", RenderingSystem::getInstance().getDefaultShader());
    backpackGameObject->addComponent(&backpackMesh);


    GameObject* backpackGameObject2 = mainScene.addGameObjectToScene("bp2");
    MeshComponent backpackMesh2 = MeshComponent("backpack/backpack.obj", RenderingSystem::getInstance().getDefaultShader());
    backpackGameObject2->addComponent(&backpackMesh2);
    backpackGameObject2->attachToGameObject(backpackGameObject);
    backpackGameObject2->translate(glm::vec3(4.0f, 0.0f, 0.0f));

    double currentFrame;
    double lastFrame = glfwGetTime();
    double deltaTime;
    unsigned int counter = 0;

    while(!glfwWindowShouldClose(renderingSystem.getWindow()))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        counter++;
        if(deltaTime >= 1.0 / 30)
        {
            std::string FPS = std::to_string((1.0 / deltaTime) * counter);
            std::string ms = std::to_string((deltaTime / counter) * 1000);
            std::string newTitle = "Engine - " + FPS + "FPS / " + ms + "ms";
            glfwSetWindowTitle(renderingSystem.getWindow(), newTitle.c_str());
            lastFrame = currentFrame;
            counter = 0;
        }

        //background colour
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        renderingSystem.getCamera().Inputs(renderingSystem.getWindow());
        renderingSystem.getCamera().updateMatrix(45.0f, 0.1f, 100.0f);

        mainScene.update();

        //draw
        //light.Draw(renderingSystem.getLightShader(), camera);
        //backpack.rotate();
        //backpack.translate(glm::vec3(0.0f, 0.01f * sin(glfwGetTime()), 0.0f));

        backpackGameObject->rotate(glm::vec3(0.0f, 0.01f, 0.0f));



        glfwSwapBuffers(renderingSystem.getWindow());
        glfwPollEvents();
    }

    //clean up
    renderingSystem.getDefaultShader().Delete();
    glfwDestroyWindow(renderingSystem.getWindow());
    glfwTerminate();

    return 0;
}
