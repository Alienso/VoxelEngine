//
// Created by Alienson on 23.4.2024..
//

#ifndef VOXEL_SKYBOX_H
#define VOXEL_SKYBOX_H


#include "Entity.h"

class Skybox : public Entity {
public:
    Skybox();
    void onUpdate(float deltaTime) override;
    void render() override;

    static float skyboxVertices[108];
    static std::vector<const char *> resourcePath;
};


#endif //VOXEL_SKYBOX_H
