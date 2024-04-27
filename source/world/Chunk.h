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
    Chunk(int x, int y, int z) : x(x), y(y), z(z), pos({x,y,z}) {
        memset(&blocks, 0, sizeof(blocks));
    };

    [[nodiscard]] static glm::uvec3 getRelativeChunkPos(glm::vec3 pos);
    [[nodiscard]] int getHeightAt(int posX, int posZ) const;

    constexpr static glm::vec3 posFromIndex(int i){ //TODO x and z???
        int y = i / (CHUNK_SIZE*CHUNK_SIZE);
        int plane = i % (CHUNK_SIZE*CHUNK_SIZE);
        int x = plane / CHUNK_SIZE;
        int z = plane % CHUNK_SIZE;
        return {x,y,z};
    }
    constexpr static uint16_t indexFromPos(int x, int y, int z){
        return y*CHUNK_SIZE*CHUNK_SIZE + z*CHUNK_SIZE + x;
    }

public:
    static inline const int CHUNK_SIZE = 16;

    const int x, y, z;
    const glm::ivec3 pos;
    int heightMap[CHUNK_SIZE*CHUNK_SIZE];
    uint16_t blocks[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE];
    bool loaded = true;

};


#endif //VOXEL_CHUNK_H
