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
    uint16_t blocks[4096];
    bool loaded;

    /* this is blocks layout
     * @ ---> x
     * |
     * v
     * z
     */
    constexpr static glm::vec3 posFromIndex(int i){ //TODO optimize? //TODO x and z???
        int y = i / 256;
        int plane = i % 256;
        int z = plane / 16;
        int x = plane % 16;
        return {z,y,x};
    }
    constexpr static uint16_t indexFromPos(int x, int y, int z){
        return y*256 + z*16 + x;
    }

};


#endif //VOXEL_CHUNK_H
