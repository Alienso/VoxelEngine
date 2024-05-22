//
// Created by Alienson on 15.5.2024..
//

#ifndef VOXEL_WATERGEN_H
#define VOXEL_WATERGEN_H


#include "PerlinNoise.h"
#include <cstdlib>

class Chunk;
class ChunkProvider;

class WaterGen {
public:
    explicit WaterGen();
    void decorate(Chunk* chunk, ChunkProvider& chunkProvider);

private:
    PerlinNoise perlin{(unsigned int)(rand() * 100000) % 100000};

    const int height;
    const int width;

    int amplitude = 10;
    float scale = 0.04;
    int octaves = 2;
    float persistance = 0.5f;
    float lacunarity = 2.0;
    float threshold = 5.0f;
};


#endif //VOXEL_WATERGEN_H
