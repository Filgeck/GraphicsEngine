//
// Created by Filipp Kondrashov on 08/07/2022.
//

#ifndef GRAPHICSENGINE_GAMEOBJECT_H
#define GRAPHICSENGINE_GAMEOBJECT_H

#include <string>
#include <vector>
#include <iostream>
#include "Object.h"
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

using std::string;
using std::vector;
using glm::vec3;
using glm::mat4;


class GameObject : public Object{
public:
    GameObject(string nm);
    string getName();
    void setName(string newName);

    void attachToGameObject(GameObject* newParent);
    void addChild(GameObject* newChild);

    mat4 getMatrix() override;

    void addComponent(Component* newComponent);

    void start() override;
    void update() override;

protected:
    string name;
    GameObject* parent;
    vector<GameObject*> children;
    vector<Component*> components;
};


#endif //GRAPHICSENGINE_GAMEOBJECT_H
