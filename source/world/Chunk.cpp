//
// Created by Alienson on 21.4.2024..
//

#include "Chunk.h"

/**
 * For given worldPosition returns position relative to chunk
 */
glm::uvec3 Chunk::getRelativeChunkPos(glm::vec3 pos) {
    int posX = (int)floor(pos.x) % CHUNK_SIZE;
    int posZ = (int)floor(pos.z) % CHUNK_SIZE;
    int posY = (int)floor(pos.y) % CHUNK_SIZE;

    if (posX < 0)
        posX = CHUNK_SIZE + posX;
    if (posZ < 0)
        posZ = CHUNK_SIZE + posZ;
    if (posY < 0)
        posY = CHUNK_SIZE + posY;

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

void Chunk::setBlockAt(glm::ivec3 p, uint16_t block) {
    blocks[p.y][p.x][p.z] = block;
}

/**
 * Generates a solid chunk
 */
Chunk *Chunk::generateSolidChunk(int x, int y, int z) {
    auto* chunk = new Chunk(x,y,z);
    /*memset(&chunk->blocks, 1, sizeof(blocks)); //????
    memset(&chunk->heightMap, 1, sizeof(heightMap));*/

    for (int _y=0; _y<Chunk::CHUNK_SIZE; _y++){
        for (int _x = 0; _x<Chunk::CHUNK_SIZE; _x++){
            for (int _z = 0; _z<Chunk::CHUNK_SIZE; _z++){
                chunk->blocks[_y][_x][_z] = 1;
            }
        }
    }
    return chunk;
}

/**
 * Given worldPos returns position for chunk
 */
glm::ivec3 Chunk::worldToChunkPos(float x, float y, float z) {
    return  { (int)floorf(x / Chunk::CHUNK_SIZE), (int)floorf(y / Chunk::CHUNK_SIZE), (int)floorf(z / Chunk::CHUNK_SIZE) };
}

/**
 * Given chunk Pos returns worldPos
 */
glm::vec3 Chunk::chunkToWorldPos(int posX, int posY, int posZ) const {
    return {this->pos.x * Chunk::CHUNK_SIZE + posX,
            this->pos.y * Chunk::CHUNK_SIZE + posY,
            this->pos.z * Chunk::CHUNK_SIZE + posZ};
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
