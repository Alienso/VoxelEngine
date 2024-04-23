//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_ENTITY_H
#define INC_3DTEST_ENTITY_H

#include "glm/glm.hpp"
#include "../../util/AxisAlignedBB.h"
#include "../render/EntityRenderer.h"
#include "../render/Material.h"

class BufferData;

class Entity {

public:
    Entity(Material& material);
    virtual ~Entity();

    virtual void onUpdate(float deltaTime);
    virtual void render();

    //TODO move this out, make this composite
    glm::vec3 pos = glm::vec3(0.0f);
    glm::vec3 prevPos = glm::vec3(0.0f);
    glm::vec3 motion = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 prevRotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 prevScale = glm::vec3(1.0f);

    friend class EntityRenderer;

protected:
    Material& material;
    BufferData* bufferData; //TODO make this not a pointer
    glm::mat4 modelMatrix = glm::mat4(1.0f); //TODO ?

};

#endif //INC_3DTEST_ENTITY_H
