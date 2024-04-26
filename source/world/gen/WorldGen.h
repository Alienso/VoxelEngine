//
// Created by Alienson on 23.4.2024..
//

#ifndef VOXEL_WORLDGEN_H
#define VOXEL_WORLDGEN_H


#include "world/Chunk.h"
#include "PerlinNoise.h"
#include <unordered_map>

class WorldGen {
public:
    Chunk* generateChunk(int x, int y, int z);

private:
    void generateHeightMap(Chunk* chunk);

    int toMapIndex(int x, int y);
    static uint32_t hash(uint32_t a);

    PerlinNoise perlin;
    int height = 16;
    int width = 16;

    float scale = 0.04;
    int octaves = 2;
    float persistance = 0.5f;
    float lacunarity = 2.0;
};


#endif //VOXEL_WORLDGEN_H
