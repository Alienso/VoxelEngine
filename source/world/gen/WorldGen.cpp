//
// Created by Alienson on 23.4.2024..
//

#include "WorldGen.h"
#include <cmath>

Chunk *WorldGen::generateChunk(int posX, int posY, int posZ) {

    auto* chunk = new Chunk(posX, posY, posZ);
    generateHeightMap(chunk);

    for (int y=0; y<16; y++){ //for each layer(height)
        for (int x = 0; x<16; x++){
            for (int z = 0; z<16; z++){
                if (y <= chunk->heightMap[x*16 + z])
                    chunk->blocks[Chunk::indexFromPos(x,y,z)] = 1;
            }
        }
    }

    return chunk;
}

void WorldGen::generateHeightMap(Chunk *chunk) {

    int heightMapIndex = 0;
    for (int z = 0 ; z <  height; z++) {
        for (int x = 0 ; x < width; x++) {

            float localAmplitude = 20;
            float frequency = 1;
            float noiseHeight = 0;

            for (int i = 0; i < octaves; i++) {
                float sampleX = (float)(x + chunk->x * 16) * scale * frequency;
                float sampleZ = (float)(z + chunk->z * 16) * scale * frequency;
                float perlinValue = (float)perlin.noise((double)sampleX, (double)sampleZ, 0) * 2 - 1;
                noiseHeight += perlinValue * localAmplitude;

                localAmplitude *= persistance;
                frequency *= lacunarity;
            }

            if (noiseHeight < 0){
                noiseHeight = 0;
            }

            chunk->heightMap[heightMapIndex++] = (int)roundf(noiseHeight);
        }
    }

}

uint32_t WorldGen::hash(uint32_t a){
    a = (a + 0x7ed55d16) + (a << 12);
    a = (a ^ 0xc761c23c) ^ (a >> 19);
    a = (a + 0x165667b1) + (a << 5);
    a = (a + 0xd3a2646c) ^ (a << 9);
    a = (a + 0xfd7046c5) + (a << 3);
    a = (a ^ 0xb55a4f09) ^ (a >> 16);
    return a;
}

int WorldGen::toMapIndex(int x, int y) {
    return (53 + hash(y)) * 53 + hash(x);
}

