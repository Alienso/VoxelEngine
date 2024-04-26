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

class CullMesher {
public:
    void generateMeshes(std::unordered_map<uint16_t, Mesh*>& terrainMeshes,
                       const ChunkProvider& chunkProvider);

private:
    void addVerticesToArray(const Chunk &chunk, uint16_t blockId, int chunkPos, const ChunkProvider& chunkProvider);

    std::unordered_map<uint16_t, std::vector<Vertex>> verticesMap;
};


#endif //VOXEL_CULLMESHER_H
