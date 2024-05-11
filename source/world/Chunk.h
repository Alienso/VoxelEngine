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
#include "gen/WorldGen.h"

#include <cstring>
#include <cstdint>

class Chunk {
public:
    Chunk(int x, int y, int z) : x(x), y(y), z(z), pos({x,y,z}) {
        memset(&blocks, 0, sizeof(blocks));
    };

    [[nodiscard]] static Chunk* generateSolidChunk(int x, int y, int z);
    [[nodiscard]] static glm::uvec3 getRelativeChunkPos(glm::vec3 pos);
    [[nodiscard]] int getHeightAt(int posX, int posZ) const;
    [[nodiscard]] uint16_t getBlockAt(int x, int y, int z) const;
    [[nodiscard]] uint16_t getBlockAt(glm::ivec3) const;
    void setBlockAt(glm::ivec3 p, uint16_t block);

    [[nodiscard]] static glm::ivec3 worldToChunkPos(float x, float y, float z);


public:
    static inline const int CHUNK_SIZE = 16;

    const int x, y, z;
    const glm::ivec3 pos;
    bool isLoaded = true;
    bool isDecorated = false;

private:
    int heightMap[CHUNK_SIZE][CHUNK_SIZE]; //TODO maybe dont have this isLoaded if chunk is not visible?
    uint16_t blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

    friend WorldGen;
};


#endif //VOXEL_CHUNK_H
