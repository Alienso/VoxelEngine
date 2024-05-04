//
// Created by Alienson on 23.4.2024..
//

#ifndef VOXEL_CULLMESHER_H
#define VOXEL_CULLMESHER_H

#include <unordered_map>
#include "glm/glm.hpp"
#include "render/Mesh.h"
#include "world/Chunk.h"

#include "util/Util.h"
#include "world/ChunkProvider.h"

struct ChunkVertexOffsetData{
    std::vector<uint16_t> blockIds;
    std::vector<size_t> vertexOffsets;
};

class CullMesher {
public:

    CullMesher();

    void generateMeshes(std::unordered_map<uint16_t, Mesh*>& terrainMeshes, const ChunkProvider& chunkProvider);
    void updateMeshes(const std::vector<Chunk *> &chunksToRemove, std::unordered_map<uint16_t, Mesh *>& terrainMeshes, ChunkProvider& chunkProvider);

    void invalidateChunkCache(Chunk *chunk);

private:
    void generateVerticesForBlockChunk(const Chunk &chunk, const Block& block, glm::ivec3 posInChunk, const ChunkProvider& chunkProvider);
    static Block& getAdjacentBlock(Chunk *chunk, glm::ivec3 pos, const EnumFacing* side, const ChunkProvider &provider);
    void addVertices(const Block& block, glm::ivec3 posOffset, const Chunk& chunk);
    void addVerticesForSide(const Block& block, glm::ivec3 posOffset, const EnumFacing *side, const Chunk& chunk);

    std::unordered_map<uint16_t, std::vector<Vertex>> verticesForBlockMap;
    std::unordered_map<glm::ivec3, std::unordered_map<uint16_t ,std::vector<Vertex>>, GlmVec3Functions, GlmVec3Functions> verticesForBlockChunkMap;

};


#endif //VOXEL_CULLMESHER_H
