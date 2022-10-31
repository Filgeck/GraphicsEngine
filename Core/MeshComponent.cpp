//
// Created by Filipp Kondrashov on 08/07/2022.
//

#include "MeshComponent.h"
#include "../RenderSystem/RenderingSystem.h"
#include "GameObject.h"
#include <glm/gtx/string_cast.hpp>

MeshComponent::MeshComponent(string path, Shader& shader) : model(path.c_str()), shader(shader) {
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
}

void MeshComponent::start() {
    Component::start();
}

void MeshComponent::update() {
    Component::update();
    model.Draw(shader, RenderingSystem::getInstance().getCamera(), Component::getMatrix());
}

