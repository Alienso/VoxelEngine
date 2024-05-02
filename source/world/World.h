//
// Created by Alienson on 20.4.2024..
//

#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "glm/glm.hpp"
#include "Chunk.h"
#include "entity/LightSource.h"
#include "render/Mesh.h"
#include "world/gen/WorldGen.h"
#include "world/gen/CullMesher.h"
#include "render/buffer/FrameBuffer.h"
#include "ChunkProvider.h"
#include "render/WorldRenderer.h"

#include <unordered_map>

class World {
public:
    World();

    void onRender();
    void onUpdate(float deltaTime);
    void onImGuiRender();

private:
    void updateTerrain();
    void handleCollision();

private:
    CullMesher cullMesher;
    ChunkProvider chunkProvider;
    WorldRenderer worldRenderer;

    std::vector<Entity> entities;

    int currentTerrainHeight = 1;
};


#endif //VOXEL_WORLD_H
