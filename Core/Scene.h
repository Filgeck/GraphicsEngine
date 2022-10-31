//
// Created by Filipp Kondrashov on 09/07/2022.
//

#ifndef GRAPHICSENGINE_SCENE_H
#define GRAPHICSENGINE_SCENE_H

#include <vector>
#include <string>
#include "GameObject.h"

using std::vector;
using std::string;



class Scene {
public:
    Scene();
    GameObject* addGameObjectToScene(string nm);

    void update();

private:
    vector<GameObject*> objects;

};


#endif //GRAPHICSENGINE_SCENE_H
