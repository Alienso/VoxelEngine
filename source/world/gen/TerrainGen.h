//
// Created by Alienson on 23.4.2024..
//

#ifndef VOXEL_TERRAINGEN_H
#define VOXEL_TERRAINGEN_H

#include "PerlinNoise.h"
#include <unordered_map>
#include <cstdint>

class Chunk;

class TerrainGen {
public:
    TerrainGen();
    Chunk* generateChunk(int x, int y, int z);

private:
    void generateHeightMap(Chunk* chunk);

    PerlinNoise perlin;
    const int height;
    const int width;

    int amplitude = 10;
    float scale = 0.04;
    int octaves = 2;
    float persistance = 0.5f;
    float lacunarity = 2.0;
};


#endif //VOXEL_TERRAINGEN_H
