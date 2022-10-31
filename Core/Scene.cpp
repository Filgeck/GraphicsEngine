//
// Created by Filipp Kondrashov on 09/07/2022.
//

#include "Scene.h"

Scene::Scene() {

}

GameObject* Scene::addGameObjectToScene(string nm) {
    GameObject* newGameObject = new GameObject(nm);
    objects.push_back(newGameObject);
    return newGameObject;
}

void Scene::update() {
    for (GameObject* object : objects) {
        object->update();
    }
}




