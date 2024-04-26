//
// Created by Alienson on 23.4.2024..
//

#include "CullMesher.h"
#include "Global.h"
#include "world/Blocks.h"

void CullMesher::generateMeshes(std::unordered_map<uint16_t, Mesh *> &terrainMeshes, const ChunkProvider &chunkProvider) {

    Mesh* currentMesh;
    verticesMap.clear();

    for (auto& it : chunkProvider.getChunks()){
        Chunk* chunk = it.second;
        for (int b=0; b<4096; b++){
            auto block = chunk->blocks[b];
            if (block != Blocks::AIR->getId()){
                addVerticesToArray(*chunk, block, b, chunkProvider);
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

void CullMesher::addVerticesToArray(const Chunk &chunk, uint16_t blockId, int chunkPos, const ChunkProvider& chunkProvider) {

    float* cubeData = &Global::cubeVertices[0];
    glm::vec3 posOffset = Chunk::posFromIndex(chunkPos) + glm::vec3(chunk.x * Chunk::CHUNK_SIZE, chunk.y * Chunk::CHUNK_SIZE, chunk.z * Chunk::CHUNK_SIZE);
    for (size_t i=0; i<Global::cubeVertices.size(); i+=8){
        verticesMap[blockId].emplace_back(glm::vec3{cubeData[i] + posOffset.x, cubeData[i+1] + posOffset.y, cubeData[i+2] + posOffset.z},
                                        glm::vec3{cubeData[i+3], cubeData[i+4], cubeData[i+5]},
                                        glm::vec2{cubeData[i+6], cubeData[i+7]});
    }
}
