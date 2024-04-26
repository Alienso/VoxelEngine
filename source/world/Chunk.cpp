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
    int index = posZ * CHUNK_SIZE + posX;
    return heightMap[index];
}
