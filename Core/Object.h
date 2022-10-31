//
// Created by Filipp Kondrashov on 11/07/2022.
//

#ifndef GRAPHICSENGINE_OBJECT_H
#define GRAPHICSENGINE_OBJECT_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

using std::string;
using std::vector;
using glm::vec3;
using glm::mat4;


class Object {
public:
    virtual void start();
    virtual void update();

    void translate(vec3 direction);
    void rotate(vec3 direction);
    void setPosition(vec3 newPosition);
    vec3 getPosition();
    void setRotation(vec3 newRotation);
    vec3 getRotation();
    void setScale(vec3 newScale);
    vec3 getScale();

    void updateMatrix();

    virtual mat4 getMatrix();

    mat4 matrix;

protected:
    vec3 position;
    vec3 rotation;
    vec3 scale;

};


#endif //GRAPHICSENGINE_OBJECT_H
