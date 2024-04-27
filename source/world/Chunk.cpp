//
// Created by Alienson on 21.4.2024..
//

#include "Chunk.h"

glm::uvec3 Chunk::getRelativeChunkPos(glm::vec3 pos) {
    int posX = (int)floor(pos.x) % CHUNK_SIZE;
    int posZ = (int)floor(pos.z) % CHUNK_SIZE;
    int posY = (int)floor(pos.y) % CHUNK_SIZE;

    if (posX < 0)
        posX = CHUNK_SIZE + posX;
    if (posZ < 0)
        posZ = CHUNK_SIZE + posZ;

    return { posX, posY, posZ};
}
int Chunk::getHeightAt(int posX, int posZ) const {
    return heightMap[posX][posZ];
}

uint16_t Chunk::getBlockAt(int posX, int posY, int posZ) const {
    return blocks[posY][posX][posZ];
}

uint16_t Chunk::getBlockAt(glm::ivec3 p) const {
    return blocks[p.y][p.x][p.z];
}

/*constexpr static glm::vec3 posFromIndex(int i){ //TODO x and z???
    int y = i / (CHUNK_SIZE*CHUNK_SIZE);
    int plane = i % (CHUNK_SIZE*CHUNK_SIZE);
    int x = plane / CHUNK_SIZE;
    int z = plane % CHUNK_SIZE;
    return {x,y,z};
}
constexpr static uint16_t indexFromPos(int x, int y, int z){
    return y*CHUNK_SIZE*CHUNK_SIZE + z*CHUNK_SIZE + x;
}*/
