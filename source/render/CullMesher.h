//
// Created by Alienson on 23.4.2024..
//

#ifndef VOXEL_CULLMESHER_H
#define VOXEL_CULLMESHER_H

#include <unordered_map>
#include "glm/glm.hpp"
#include "render/Mesh.h"
#include "util/Util.h"


class Chunk;
class ChunkProvider;
class WorldRenderer;

class EnumFacing;
class Block;

struct ChunkVertexOffsetData{
    std::vector<uint16_t> blockIds;
    std::vector<size_t> vertexOffsets;
};

class CullMesher {
public:
    CullMesher();

    friend WorldRenderer;

    bool generateMeshes(terrainMeshMap& terrainMeshes, ChunkProvider& chunkProvider);
    bool updateMeshes(const std::vector<Chunk *> &chunksToRemove, terrainMeshMap& terrainMeshes, ChunkProvider& chunkProvider);

    void invalidateChunkCache(Chunk *chunk);

private:
    void generateVerticesForBlockChunk(const Chunk &chunk, const Block& block, glm::ivec3 posInChunk, ChunkProvider& chunkProvider);
    void addVertices(const Block& block, glm::ivec3 posOffset, const Chunk& chunk, ChunkProvider& chunkProvider);
    void addVerticesForSide(const Block& block, glm::ivec3 posOffset, const EnumFacing *side, const Chunk& chunk, ChunkProvider& chunkProvider);

    static Block& getAdjacentBlock(Chunk *chunk, glm::ivec3 pos, const EnumFacing* side, const ChunkProvider &provider);
    static float getAOValue(int vertexIndex, size_t side, float* vertexPos, ChunkProvider& chunkProvider);

    std::unordered_map<glm::ivec3, std::unordered_map<uint16_t, std::vector<Vertex>>, GlmVec3Functions, GlmVec3Functions> verticesForBlockChunkMap;

    static inline bool updatingMeshes = false;
};


#endif //VOXEL_CULLMESHER_H
