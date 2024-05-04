//
// Created by Alienson on 3.5.2024..
//

#include "RayTrace.h"
#include "Configuration.h"
#include "Global.h"
#include "world/Chunk.h"
#include "world/Blocks.h"
#include "world/World.h"

RayTraceResult RayTrace::traceScene(double xPos, double yPos){

    glm::vec2 uv = glm::vec2(xPos,yPos) / glm::vec2(Configuration::wWidth,Configuration::wHeight);

    uv = uv * glm::vec2(2.0) - glm::vec2(1.0);//transform from [0,1] to [-1,1]
    uv.x *= (float)(Configuration::wWidth)/(float)Configuration::wHeight; //aspect fix

    //glm::vec3 rayDir = normalize(glm::vec4(glm::vec3(0,0,1) + glm::vec3(uv.x,uv.y,0),1) * Global::camera.transformationMatrix);
    glm::vec3 rayDir = Global::camera.front;

    Chunk* chunk;
    glm::vec3 rayPos = Global::camera.pos;
    uint16_t block = Blocks::AIR->getId();
    for(int i=0; i<8; i++){
        chunk = Global::world->getChunkProvider().getChunkAtWorldPos(rayPos.x, rayPos.y, rayPos.z);
        if (chunk != nullptr) {
            glm::ivec3 blockPos = Chunk::getRelativeChunkPos(rayPos);
            block = chunk->getBlockAt(blockPos);
            if (block != Blocks::AIR->getId())
                break;
        }
        rayPos += rayDir;
    }

    if(block == Blocks::AIR->getId())
        return RayTraceResult(false);

    //TODO do more precise calculation for collision box and if that fails continue with tracing
    glm::ivec3 hitPos{(int)rayPos.x, (int)rayPos.y, (int)rayPos.z};

    const EnumFacing* side = getSideHit(rayPos, hitPos);

    return {true, chunk, hitPos, rayDir, nullptr, side};
}

const EnumFacing *RayTrace::getSideHit(glm::vec3 rayPos, glm::ivec3 hitPos) {
    const EnumFacing* sides[3] = {nullptr, nullptr, nullptr};
    if (rayPos.x < (float)hitPos.x)
        sides[0] = EnumFacing::NORTH;
    else sides[0] = EnumFacing::SOUTH;
    if (rayPos.y < (float)hitPos.y)
        sides[1] = EnumFacing::DOWN;
    else sides[1] = EnumFacing::UP;
    if (rayPos.z < (float)hitPos.z)
        sides[2] = EnumFacing::WEST;
    else sides[2] = EnumFacing::EAST;

    glm::vec3 rayDir = glm::vec3((float)hitPos.x + 0.5f, (float)hitPos.y + 0.5f, (float)hitPos.z + 0.5f) - rayPos;
    if (rayDir.x > rayDir.y){
        if (rayDir.x > rayDir.z)
            return sides[0];
        else return sides[2];
    }
    else{
        if (rayDir.y > rayDir.z) {
            return sides[1];
        }
        return sides[2];
    }
}
