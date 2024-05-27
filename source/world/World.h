//
// Created by Alienson on 20.4.2024..
//

#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "glm/glm.hpp"
#include "Chunk.h"
#include "entity/SunEntity.h"
#include "render/Mesh.h"
#include "world/gen/TerrainGen.h"
#include "render/CullMesher.h"
#include "render/buffer/FrameBuffer.h"
#include "ChunkProvider.h"
#include "render/WorldRenderer.h"
#include "world/biome/BiomeProvider.h"
#include "util/ts_queue.h"

#include <unordered_map>
#include <mutex>
#include <queue>
#include <atomic>

struct BufferDataCommand{
    float* vertexData;
    size_t length;
    BufferData* bufferData;
    std::condition_variable& cv;
    BufferDataCommand(float* vertexData, size_t length, BufferData* bufferData, std::condition_variable& cv) : vertexData(vertexData),
                                                                                                   length(length), bufferData(bufferData), cv(cv){}
};

class World {
public:
    World();

    void onRender();
    void onUpdate(float deltaTime);
    void onImGuiRender();

    void genBufferData(float* vertexData, size_t length, BufferData* bufferData, std::condition_variable& cv);

    void updateTerrain();
    static int getTimeOfDay();

    [[nodiscard]] ChunkProvider& getChunkProvider();

    void updateBufferData();

    void deleteBufferData(BufferData *pData);

private:
    void handleCollision();

private:
    ChunkProvider chunkProvider;
    WorldRenderer worldRenderer;

    std::vector<Entity*> entities;

    ts_queue <BufferDataCommand> bufferDataCommandQueue; //TODO refactor placement
    std::vector<BufferData*> renderBufferData; //TODO maybe make this non pointers for faster access?

    static int timeOfDay;

    void checkIfPlayerSwitchedChunk(); //Temp
    bool playerChangedChunk = false;
};


#endif //VOXEL_WORLD_H
