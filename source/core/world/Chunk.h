//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_CHUNK_H
#define VOXEL_CHUNK_H


#include "Block.h"

#include <cstring>
#include <cstdint>

class Chunk {
public:
    Chunk(int x, int y, int z) : x(x), y(y), z(z) {
        memset(&blocks, 0, sizeof(blocks));
        blocks[0] = 1;
    };

    const int x, y, z;
    int heightMap[256];
    bool loaded;
    uint16_t blocks[4096];

    static glm::vec3 posFromIndex(int i);

};


#endif //VOXEL_CHUNK_H
