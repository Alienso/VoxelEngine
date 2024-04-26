//
// Created by Alienson on 26.4.2024..
//

#include "ChunkProvider.h"

ChunkProvider::ChunkProvider() {
    int worldSize = 3;
    for (int i=-worldSize; i<worldSize; i++ ){
        for (int j=-worldSize; j<worldSize; j++){
            glm::vec3 pos = {i,0,j};
            Chunk* chunk = worldGen.generateChunk(i,0,j);
            chunkMap[pos] = chunk;
        }
    }
}

ChunkProvider::~ChunkProvider() {
    for (auto it : chunkMap)
        delete it.second;
}

Chunk &ChunkProvider::getChunkAt(int x, int y, int z) {
    if (auto it = chunkMap.find({x,y,z}); it != chunkMap.end()){
        return *it->second;
    }
    //generate chunk and return it; maybe it is generated but not loaded? TODO
    auto* chunk = new Chunk(x,y,z);
    chunkMap[{x,y,z}] = chunk;
    return *chunk;
}

const ChunkMap &ChunkProvider::getChunks() const {
    return chunkMap;
}

/*Chunk &ChunkProvider::getAdjacentChunk(EnumSide side) const { //TODO
    return *this;
}*/
