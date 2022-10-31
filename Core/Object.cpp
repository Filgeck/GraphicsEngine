//
// Created by Filipp Kondrashov on 11/07/2022.
//

#include "Object.h"

//remove
#include <iostream>
#include <glm/gtx/string_cast.hpp>

void Object::start() {

}

void Object::update() {
    updateMatrix();
}

void Object::translate(vec3 direction) {
    position.x += direction.x;
    position.y += direction.y;
    position.z += direction.z;
}

void Object::rotate(vec3 direction) {
    rotation.x += direction.x;
    rotation.y += direction.y;
    rotation.z += direction.z;
}

void Object::setPosition(vec3 newPosition) {
    position = newPosition;
}

vec3 Object::getPosition() {
    return position;
}

void Object::setRotation(vec3 newRotation) {
    rotation = newRotation;
}

vec3 Object::getRotation() {
    return rotation;
}

void Object::setScale(vec3 newScale) {
    scale = newScale;
}

vec3 Object::getScale() {
    return scale;
}

void Object::updateMatrix() {
    mat4 trans = mat4(1.0f);
    mat4 rot = mat4(1.0f);
    mat4 sca = mat4(1.0f);

    trans = glm::translate(trans, position);
    glm::quat r = glm::quat(rotation);
    rot = glm::mat4_cast(r);
    sca = glm::scale(sca, scale);
    matrix = trans*rot*sca;
}

mat4 Object::getMatrix() {
    return matrix;
}
