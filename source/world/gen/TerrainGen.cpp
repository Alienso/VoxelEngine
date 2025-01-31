//
// Created by Alienson on 23.4.2024..
//

#include "TerrainGen.h"
#include <cmath>
#include "world/Chunk.h"
#include "world/Blocks.h"

TerrainGen::TerrainGen() : height(Chunk::CHUNK_SIZE), width(Chunk::CHUNK_SIZE) {}

Chunk *TerrainGen::generateChunk(int posX, int posY, int posZ) {

    auto* chunk = new Chunk(posX, posY, posZ);
    generateHeightMap(chunk);

    for (int y=0; y<Chunk::CHUNK_SIZE; y++){
        for (int x = 0; x<Chunk::CHUNK_SIZE; x++){
            for (int z = 0; z<Chunk::CHUNK_SIZE; z++){
                if (y <= chunk->heightMap[x][z])
                    chunk->blocks[y][x][z] = Blocks::GRASS_BLOCK->getId();
            }
        }
    }

    return chunk;
}

void TerrainGen::generateHeightMap(Chunk *chunk) {

    for (int z = 0 ; z <  height; z++) { //TODO invert order for cache locality
        for (int x = 0 ; x < width; x++) {

            float localAmplitude = (float)amplitude;
            float frequency = 1;
            float noiseHeight = 0;

            for (int i = 0; i < octaves; i++) {
                float sampleX = (float)(x + chunk->x * Chunk::CHUNK_SIZE) * scale * frequency;
                float sampleZ = (float)(z + chunk->z * Chunk::CHUNK_SIZE) * scale * frequency;
                float perlinValue = (float)perlin.noise((double)sampleX, (double)sampleZ, 0) * 2 - 1;
                noiseHeight += perlinValue * localAmplitude;

                localAmplitude *= persistance;
                frequency *= lacunarity;
            }

            if (noiseHeight < 0){
                noiseHeight = 0;
            }

            chunk->heightMap[x][z] = (int)roundf(noiseHeight);
        }
    }

}

