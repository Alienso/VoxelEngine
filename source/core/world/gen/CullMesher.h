//
// Created by Alienson on 23.4.2024..
//

#ifndef VOXEL_CULLMESHER_H
#define VOXEL_CULLMESHER_H

#include <unordered_map>
#include "glm/glm.hpp"
#include "../../render/Mesh.h"
#include "../Chunk.h"

#include "../../../util/Util.cpp"

class CullMesher {
public:
    void generateMeshes(std::unordered_map<uint16_t, Mesh*>& terrainMeshes,
                        std::unordered_map<glm::u32vec3, Chunk*, GlmVec3Functions, GlmVec3Functions>& chunkMap);
};


#endif //VOXEL_CULLMESHER_H
