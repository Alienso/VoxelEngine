//
// Created by Alienson on 20.4.2024..
//

#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "glm/glm.hpp"
#include "Chunk.h"
#include "../entity/LightSource.h"
#include "../render/Mesh.h"

#include <unordered_map>

struct KeyFuncs
{
    size_t operator()(const glm::u32vec3& k) const {
        return std::hash<uint32_t>()(k.x) ^ std::hash<uint32_t>()(k.y) ^ std::hash<uint32_t>()(k.z);
    }

    bool operator()(const glm::u32vec3& a, const glm::u32vec3& b) const {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};

class World {
public:
    World();
    ~World();

    void onRender();
    void onUpdate(float deltaTime);
    void onImGuiRender();

    Chunk& getChunk(int x, int y, int z);
private:

    void renderTerrain();

    std::unordered_map<glm::u32vec3, Chunk*, KeyFuncs, KeyFuncs> chunkMap;
    std::vector<LightSource> lightSources;

    std::unordered_map<uint16_t, Mesh*> terrainMeshes; //TODO memory managment

    //TODO MOVE
    float ambientStrength = 0.1;
    float specularStrength = 0.5;
    int shininess = 32;
};


#endif //VOXEL_WORLD_H
