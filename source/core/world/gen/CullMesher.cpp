//
// Created by Alienson on 23.4.2024..
//

#include "CullMesher.h"
#include "Global.h"

void CullMesher::generateMeshes(std::unordered_map<uint16_t, Mesh *> &terrainMeshes,
                                std::unordered_map<glm::u32vec3, Chunk *, GlmVec3Functions, GlmVec3Functions> &chunkMap) {

    Mesh* currentMesh;
    std::unordered_map<int, std::vector<Vertex>> verticesMap;

    for (auto& it : chunkMap){
        Chunk* chunk = it.second;
        for (int b=0; b<4096; b++){
            auto block = chunk->blocks[b];
            if (block != 0){
                float* cubeData = Global::cubeVertices;
                glm::vec3 posOffset = Chunk::posFromIndex(b) + glm::vec3(chunk->x * 16, chunk->y * 16, chunk->z * 16);
                for (int i=0; i<288; i+=8){
                    verticesMap[block].emplace_back(glm::vec3{cubeData[i] + posOffset.x, cubeData[i+1] + posOffset.y, cubeData[i+2] + posOffset.z},
                                          glm::vec3{cubeData[i+3], cubeData[i+4], cubeData[i+5]},
                                          glm::vec2{cubeData[i+6], cubeData[i+7]});
                }
            }
        }
    }

    for (const auto& it : verticesMap) {
        if (it.second.empty())
            continue;
        currentMesh = Mesh::fromRawData((float *) (&(it.second[0])), it.second.size() * 8);
        if (auto meshIter = terrainMeshes.find(it.first); meshIter != terrainMeshes.end()){
            delete meshIter->second;
        }
        terrainMeshes[it.first] = currentMesh;
    }
}
