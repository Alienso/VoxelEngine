//
// Created by Alienson on 3.5.2024..
//

#ifndef VOXEL_TREEGENERATOR_H
#define VOXEL_TREEGENERATOR_H


#include <cstdlib>
#include "PerlinNoise.h"
#include "world/Chunk.h"

class ChunkProvider;

class TreeGenerator {
public:
    explicit TreeGenerator();
    void decorate(Chunk* chunk, ChunkProvider& chunkProvider);

private:
    void generateTree(glm::vec3 pos, ChunkProvider& chunkProvider);

    PerlinNoise perlinNoise{(unsigned int)(rand() * 100000) % 100000};
    float scale;
    float threshold;
};


#endif //VOXEL_TREEGENERATOR_H
