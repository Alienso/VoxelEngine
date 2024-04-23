//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_LIGHTSOURCE_H
#define VOXEL_LIGHTSOURCE_H


#include "Entity.h"
#include "../../Asset.h"

class LightSource : public Entity{

public:

    LightSource(glm::vec3 pos, glm::vec3 color);

    void onUpdate(float deltaTime) override;

    void render() override;

    glm::vec3 pos;
    glm::vec3 color;
};


#endif //VOXEL_LIGHTSOURCE_H
