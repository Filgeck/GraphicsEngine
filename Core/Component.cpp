//
// Created by Filipp Kondrashov on 08/07/2022.
//

#include "Component.h"
#include "GameObject.h"

void Component::start() {
    Object::start();
}

void Component::update() {
    Object::update();       //updated matrix
}

void Component::setParent(GameObject* newParent) {
    parent = newParent;
}

mat4 Component::getMatrix(){
    return parent->getMatrix() * matrix;
}
