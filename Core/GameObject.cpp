//
// Created by Filipp Kondrashov on 08/07/2022.
//

#include "GameObject.h"

//remove
#include <iostream>
#include <glm/gtx/string_cast.hpp>

GameObject::GameObject(string nm) {
    name = nm;
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
    parent = nullptr;
}

string GameObject::getName() {
    return name;
}

void GameObject::setName(string newName) {
    name = newName;
}

void GameObject::attachToGameObject(GameObject* newParent){
    parent = newParent;
    parent->addChild(this);
}

void GameObject::addChild(GameObject* newChild) {
    children.push_back(newChild);
}

void GameObject::addComponent(Component* newComponent) {
    components.push_back(newComponent);
    newComponent->setParent(this);
}

void GameObject::start() {
    for (Component* component : components) {
        component->start();
    }
}

void GameObject::update() {
    Object::update();
    for (Component* component : components) {
        component->update();
    }
    for (GameObject* child : children){
        child->update();
    }
}

mat4 GameObject::getMatrix(){
    updateMatrix();       //makes it work
    if (parent != nullptr)
    {
        return parent->getMatrix() * matrix;
    }
    else
    {
        return matrix;
    }
}


