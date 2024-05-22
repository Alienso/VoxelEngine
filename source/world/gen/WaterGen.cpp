//
// Created by Alienson on 15.5.2024..
//

#include "WaterGen.h"
#include "world/Blocks.h"
#include "world/Chunk.h"
#include "world/ChunkProvider.h"

WaterGen::WaterGen() : height(Chunk::CHUNK_SIZE), width(Chunk::CHUNK_SIZE) {

}

void WaterGen::decorate(Chunk *chunk, ChunkProvider& chunkProvider) {
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

            if (noiseHeight > threshold) { //TODO
                int y = chunk->getHeightAt(x, z);
                for (int i = 0; i <= noiseHeight - threshold; i++) {
                    glm::vec3 pos = chunk->chunkToWorldPos(x, y, z);
                    chunkProvider.setBlockAtWorldPos(pos.x, pos.y - (float) i, pos.z, Blocks::STILL_WATER->getId());
                }
            }
        }
    }
}
