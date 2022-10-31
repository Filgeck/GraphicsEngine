 cmake_minimum_required(VERSION 3.22)
project(GraphicsEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(GraphicsEngine main.cpp RenderSystem/Shader.cpp RenderSystem/Shader.h RenderSystem/VBO.cpp RenderSystem/VBO.h RenderSystem/EBO.cpp RenderSystem/EBO.h RenderSystem/VAO.cpp RenderSystem/VAO.h RenderSystem/stb/stb_image.h RenderSystem/stb/stb.cpp RenderSystem/Texture.cpp RenderSystem/Texture.h RenderSystem/Camera.cpp RenderSystem/Camera.h RenderSystem/Mesh.cpp RenderSystem/Mesh.h RenderSystem/Model.cpp RenderSystem/Model.h Core/GameObject.cpp Core/GameObject.h Core/Component.cpp Core/Component.h Core/MeshComponent.cpp Core/MeshComponent.h RenderSystem/RenderingSystem.cpp RenderSystem/RenderingSystem.h Core/Scene.cpp Core/Scene.h Core/Object.cpp Core/Object.h)

 find_package(glfw3 REQUIRED)
 target_link_libraries(GraphicsEngine PRIVATE glfw)

 find_package(glm REQUIRED)
 target_link_libraries(GraphicsEngine PRIVATE glm::glm)

 find_package(assimp REQUIRED)
 target_link_libraries(GraphicsEngine PRIVATE assimp::assimp)


 find_package(OpenGL REQUIRED)
 target_link_libraries(GraphicsEngine PRIVATE OpenGL::GL)

 add_subdirectory(glad/)
 target_link_libraries(GraphicsEngine PRIVATE glad)

