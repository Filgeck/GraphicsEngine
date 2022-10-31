//
// Created by Filipp Kondrashov on 08/07/2022.
//

#ifndef GRAPHICSENGINE_MESHCOMPONENT_H
#define GRAPHICSENGINE_MESHCOMPONENT_H

#include "Component.h"
#include "../RenderSystem/Model.h"
#include "../RenderSystem/Shader.h"

class MeshComponent: public Component {
public:
    MeshComponent(string path, Shader& shader);
    void start() override;
    void update() override;
private:
    Model model;
    Shader& shader;
};


#endif //GRAPHICSENGINE_MESHCOMPONENT_H
