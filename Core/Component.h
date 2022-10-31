//
// Created by Filipp Kondrashov on 08/07/2022.
//

#ifndef GRAPHICSENGINE_COMPONENT_H
#define GRAPHICSENGINE_COMPONENT_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Object.h"

using glm::vec3;
using std::string;


class GameObject;

class Component : public Object{
public:
    void start() override;
    void update() override;

    mat4 getMatrix();
    void setParent(GameObject* parent);

protected:
    GameObject* parent;
};


#endif //GRAPHICSENGINE_COMPONENT_H
