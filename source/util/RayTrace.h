//
// Created by Alienson on 3.5.2024..
//

#ifndef VOXEL_RAYTRACE_H
#define VOXEL_RAYTRACE_H

#include "EnumFacing.h"
#include "entity/Entity.h"
#include "world/Chunk.h"

struct RayTraceResult{
    explicit RayTraceResult(bool hit) : hit(hit), chunk(nullptr), hitPos({}), hitVec({}), entityHit(nullptr), side(nullptr){}
    RayTraceResult(bool hit, Chunk* chunk, glm::ivec3 hitPos, glm::vec3 hitVec, Entity* entityHit, const EnumFacing* side) :
        hit(hit), chunk(chunk), hitPos(hitPos), hitVec(hitVec), entityHit(entityHit), side(side){}
    bool hit;
    Chunk* chunk;
    glm::ivec3 hitPos;
    glm::vec3 hitVec;
    Entity* entityHit;
    const EnumFacing* side;
};

class RayTrace {
public:
    static RayTraceResult traceScene(double xPos, double yPos);
private:
    static const EnumFacing* getSideHit(glm::vec3 rayPos, glm::ivec3 hitPos);
};


#endif //VOXEL_RAYTRACE_H
