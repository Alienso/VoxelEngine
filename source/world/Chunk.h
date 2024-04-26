//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_CHUNK_H
#define VOXEL_CHUNK_H

/* Chunk::blocks layout
 * @ ---> X
 * |
 * v
 * Z
 */

#include "Block.h"

#include <cstring>
#include <cstdint>

class Chunk {
public:
    Chunk(int x, int y, int z) : x(x), y(y), z(z) {
        memset(&blocks, 0, sizeof(blocks));
    };

    constexpr static glm::vec3 posFromIndex(int i){ //TODO x and z???
        int y = i / 256;
        int plane = i % 256;
        int x = plane / 16;
        int z = plane % 16;
        return {x,y,z};
    }
    constexpr static uint16_t indexFromPos(int x, int y, int z){
        return y*256 + z*16 + x;
    }

public:
    const int x, y, z;
    int heightMap[256];
    uint16_t blocks[4096];
    bool loaded = true;

};


#endif //VOXEL_CHUNK_H
