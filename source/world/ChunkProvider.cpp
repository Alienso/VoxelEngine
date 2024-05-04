//
// Created by Alienson on 26.4.2024..
//

#include "ChunkProvider.h"
#include "Chunk.h"
#include "Global.h"

ChunkProvider::ChunkProvider() {
    /*int worldSize = Global::renderDistance;
    for (int i=-worldSize; i<worldSize; i++ ){
        for (int j=-worldSize; j<worldSize; j++){
            glm::vec3 pos = {i,0,j};
            Chunk* chunk = worldGen.generateChunk(i,0,j);
            chunkMap[pos] = chunk;
        }
    }*/

    /*for (int i=-worldSize; i<worldSize; i++ ){
        for (int j=-worldSize; j<worldSize; j++){
            for (int y = -10; y<0; y++) {
                glm::vec3 pos = {i, y, j};
                Chunk *chunk = Chunk::generateChunkBlock(i,y,j);
                chunkMap[pos] = chunk;
            }
        }
    }*/
}

ChunkProvider::~ChunkProvider() {
    for (auto it : chunkMap) {
        delete it.second;
    }
    chunkMap.clear();
}

const ChunkMap &ChunkProvider::getChunks() const {
    return chunkMap;
}

Chunk *ChunkProvider::getChunkAt(int x, int y, int z) {
    if (auto it = chunkMap.find({x,y,z}); it != chunkMap.end()){
        return it->second;
    }
    return nullptr;
}

Chunk* ChunkProvider::getChunkAtWorldPos(float x, float y, float z) {
    glm::ivec3 chunkPos = Chunk::worldToChunkPos(x,y,z);
    if (const auto& it = chunkMap.find(chunkPos); it != chunkMap.end())
        return it->second;
    return nullptr; //todo this should load chunk if unavailable
}

Chunk* ChunkProvider::getAdjacentChunk(const Chunk& chunk, const EnumFacing* side) const {
    auto it = chunkMap.find(chunk.pos + side->dirVec);
    if (it != chunkMap.end())
        return it->second;
    return nullptr;
}

Chunk *ChunkProvider::generateChunkAt(int x, int y, int z) {
    //maybe it is generated but not loaded? TODO
    auto* chunk =  worldGen.generateChunk(x,y,z);
    biomeProvider.getBiomeAt(x,y,z)->decorateChunk(chunk);
    chunkMap[{x,y,z}] = chunk;
    return chunk;
}

Chunk *ChunkProvider::generateChunkAtWorldPos(const float x, const float y, const float z) {
    glm::ivec3 chunkPos = Chunk::worldToChunkPos(x,y,z);
    auto* chunk =  worldGen.generateChunk(chunkPos.x,chunkPos.y,chunkPos.z);
    chunkMap[chunkPos] = chunk;
    return chunk;
}

void ChunkProvider::deleteChunkAt(const glm::ivec3 pos) {
    if (const auto& it = chunkMap.find(pos); it != chunkMap.end()) {
        delete it->second;
        chunkMap.erase(pos);
    }
}

