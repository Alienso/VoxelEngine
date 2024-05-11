//
// Created by Alienson on 26.4.2024..
//

#include "ChunkProvider.h"
#include "Chunk.h"
#include "Global.h"

ChunkProvider::ChunkProvider() {
    /*glm::ivec3 pos = Chunk::worldToChunkPos(Global::camera.pos.x, Global::camera.pos.y, Global::camera.pos.z);
    int renderDistance = 16;
    for (int x = pos.x - renderDistance; x<=pos.x + renderDistance; x++){
        for (int z = pos.z - renderDistance; z<=pos.z + renderDistance; z++){
            if ((x - pos.x)*(x - pos.x) + (z - pos.z)*(z - pos.z) <= renderDistance * renderDistance){
                for (int y = -5; y<0; y++) {
                    glm::vec3 newPos = {x, y, y};
                    Chunk *chunk = Chunk::generateSolidChunk(x, y, z);
                    chunkMap[newPos] = chunk;
                }
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

Chunk *ChunkProvider::getChunkAt(glm::ivec3 pos) {
    if (auto it = chunkMap.find(pos); it != chunkMap.end()){
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
    //maybe it is generated but not isLoaded? TODO
    auto* chunk =  worldGen.generateChunk(x,y,z);
    chunkMap[{x,y,z}] = chunk;
    biomeProvider.getBiomeAt(x,y,z)->decorateChunk(chunk, *this);
    return chunk;
}

Chunk *ChunkProvider::generatePlainChunkAtWorldPos(const float x, const float y, const float z) {
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

uint16_t ChunkProvider::getBlockAtWorldPos(float x, float y, float z) {
    Chunk* chunk = getChunkAtWorldPos(x,y,z);
    if (chunk == nullptr)
        return 0;
    return chunk->getBlockAt(Chunk::getRelativeChunkPos({x,y,z}));
}

void ChunkProvider::setBlockAtWorldPos(float x, float y, float z, uint16_t block) {
    Chunk* chunk = getChunkAtWorldPos(x, y, z);
    if (chunk == nullptr)
        chunk = generatePlainChunkAtWorldPos(x, y, z);
    chunk->setBlockAt(Chunk::getRelativeChunkPos({x,y,z}), block);
}

