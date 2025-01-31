//
// Created by Alienson on 26.4.2024..
//

#ifndef VOXEL_CHUNKPROVIDER_H
#define VOXEL_CHUNKPROVIDER_H

#include "glm/glm.hpp"
#include "Chunk.h"
#include "util/Util.h"
#include "world/gen/TerrainGen.h"
#include "EnumFacing.h"
#include "world/biome/BiomeProvider.h"

#include <unordered_map>

typedef std::unordered_map<glm::ivec3, Chunk *, GlmVec3Functions, GlmVec3Functions> ChunkMap;

class ChunkProvider {
public:
    ChunkProvider();
    ~ChunkProvider();

    [[nodiscard]] const ChunkMap& getChunks() const;
    [[nodiscard]] Chunk* getChunkAt(int x, int y, int z);
    [[nodiscard]] Chunk* getChunkAt(glm::ivec3 pos);
    [[nodiscard]] Chunk* getChunkAtWorldPos(float x, float y, float z);
    [[nodiscard]] Chunk* getAdjacentChunk(const Chunk& chunk, const EnumFacing* side) const;

    [[nodiscard]] uint16_t getBlockAtWorldPos(float x, float y, float z);
    void setBlockAtWorldPos(float x, float y, float z, uint16_t block);

    Chunk* generateChunkAt(int x, int y, int z);
    Chunk* generatePlainChunkAtWorldPos(float x, float y, float z);

    void deleteChunkAt(glm::ivec3 pos);

private:
    ChunkMap chunkMap;
    TerrainGen worldGen;
    BiomeProvider biomeProvider;
};


#endif //VOXEL_CHUNKPROVIDER_H
