//
// Created by Alienson on 20.4.2024..
//

#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "glm/glm.hpp"
#include "Chunk.h"
#include "../entity/LightSource.h"
#include "../render/Mesh.h"
#include "gen/WorldGen.h"
#include "gen/CullMesher.h"
#include "core/render/buffer/FrameBuffer.h"

#include <unordered_map>

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
    void renderScene();
    void renderShadows();

    WorldGen worldGen;
    CullMesher cullMesher;
    FrameBuffer shadowBuffer{FRAME_BUFFER_SHADOW};
    Shader* shadowShader;

    Material* grassMat = nullptr; //TODO Temp
    std::unordered_map<glm::u32vec3, Chunk*, GlmVec3Functions, GlmVec3Functions> chunkMap;
    std::unordered_map<uint16_t, Mesh*> terrainMeshes; //TODO memory management
};


#endif //VOXEL_WORLD_H
