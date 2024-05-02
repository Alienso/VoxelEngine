//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_SUNENTITY_H
#define VOXEL_SUNENTITY_H


#include "Entity.h"
#include "Asset.h"

class SunEntity : public Entity{

public:
    explicit SunEntity(glm::vec3 pos);
    void onUpdate(float deltaTime) override;
    void render() override;

    [[nodiscard]] glm::vec3 getColor() const;
    [[nodiscard]] glm::vec3 getLightDir() const;

    glm::vec3 color = {1,1,1};
    glm::vec3 pos;

private:

};


#endif //VOXEL_SUNENTITY_H
