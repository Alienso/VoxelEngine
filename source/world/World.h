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

#include <unordered_map>

class World {
public:
    World();

    void onRender();
    void onUpdate(float deltaTime);
    void onImGuiRender();

private:
    void renderTerrain();
    void renderScene();
    void renderShadows();

    void updateTerrain();
    void handleCollision();

private:
    CullMesher cullMesher;
    ChunkProvider chunkProvider;
    std::vector<Entity> entities;

    FrameBuffer shadowBuffer{FRAME_BUFFER_SHADOW};
    Shader* shadowShader;

    std::unordered_map<uint16_t, Mesh*> terrainMeshes;
    int currentTerrainHeight = 1;
};


#endif //VOXEL_WORLD_H
