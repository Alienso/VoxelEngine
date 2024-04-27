//
// Created by Alienson on 23.4.2024..
//

#include <chrono>
#include "CullMesher.h"
#include "Global.h"
#include "world/Blocks.h"

CullMesher::CullMesher() {}


void CullMesher::generateMeshes(std::unordered_map<uint16_t, Mesh *> &terrainMeshes, const ChunkProvider &chunkProvider) {

    Mesh* currentMesh;
    verticesMap.clear();

    for (auto& it : chunkProvider.getChunks()){
        Chunk* chunk = it.second;
        for (int y=0; y<Chunk::CHUNK_SIZE; y++){
            for (int x = 0; x<Chunk::CHUNK_SIZE; x++){
                for (int z = 0; z<Chunk::CHUNK_SIZE; z++){
                    auto blockId = chunk->getBlockAt(x,y,z);
                    if (blockId != Blocks::AIR->getId()) {
                        addVerticesToArray(*chunk, blockId, {x, y, z}, chunkProvider);
                    }
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

void CullMesher::addVerticesToArray(const Chunk &chunk, const uint16_t blockId, const glm::ivec3 posInChunk, const ChunkProvider& chunkProvider) {

    glm::ivec3 posOffset = posInChunk + glm::ivec3(chunk.x * Chunk::CHUNK_SIZE, chunk.y * Chunk::CHUNK_SIZE, chunk.z * Chunk::CHUNK_SIZE);
    for (auto side : EnumFacing::sides){
        uint16_t otherBlock = getAdjacentBlock(const_cast<Chunk *>(&chunk), posInChunk, side, chunkProvider);
        if(otherBlock == Blocks::AIR->getId()) {
            addVerticesForSide(blockId, posOffset, side);
        }
    }
}

void CullMesher::addVerticesForSide(const uint16_t blockId, glm::ivec3 posOffset, const EnumFacing *side) {

    size_t offset = Global::cubeVerticesSideOffsets[side->id]; //Danger have mapper?
    float* cubeData = &Global::cubeVertices[offset];
    for (size_t i = 0; i < Global::cubeVerticesSideSize; i+=8){
        verticesMap[blockId].emplace_back(glm::vec3{cubeData[i] + (float)posOffset.x, cubeData[i+1] + (float)posOffset.y, cubeData[i+2] + (float)posOffset.z},
                                          glm::vec3{cubeData[i+3], cubeData[i+4], cubeData[i+5]},
                                          glm::vec2{cubeData[i+6], cubeData[i+7]});
    }
}

uint16_t CullMesher::getAdjacentBlock(Chunk *chunk, glm::ivec3 posInChunk, const EnumFacing* side, const ChunkProvider &provider) {

    glm::ivec3 pos = posInChunk + side->dirVec;

    if (pos.x < 0 || pos.x >= Chunk::CHUNK_SIZE ||
        pos.y < 0 || pos.y >= Chunk::CHUNK_SIZE ||
        pos.z < 0 || pos.z >= Chunk::CHUNK_SIZE) {

        chunk = provider.getAdjacentChunk(*chunk, side);
        if (chunk == nullptr) //TODO this shouldn't happen
            return 0;
        pos.x = (pos.x + Chunk::CHUNK_SIZE) % Chunk::CHUNK_SIZE;
        pos.y = (pos.y + Chunk::CHUNK_SIZE) % Chunk::CHUNK_SIZE;
        pos.z = (pos.z + Chunk::CHUNK_SIZE) % Chunk::CHUNK_SIZE;
    }

    return chunk->getBlockAt(pos);
}
