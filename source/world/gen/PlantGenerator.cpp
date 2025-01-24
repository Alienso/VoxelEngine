//
// Created by Alienson on 3.5.2024..
//

#include "PlantGenerator.h"
#include "world/Blocks.h"

PlantGenerator::PlantGenerator() {
    scale = 0.2f;
    threshold = 0.2f;
}

void PlantGenerator::decorate(Chunk *chunk) {
    for (int x = 0; x<Chunk::CHUNK_SIZE; x++){
        for (int z = 0; z<Chunk::CHUNK_SIZE; z++){
            float sampleX = (float)(x + chunk->x * Chunk::CHUNK_SIZE) * scale;
            float sampleZ = (float)(z + chunk->z * Chunk::CHUNK_SIZE) * scale;
            float perlinValue = (float)perlinNoise.noise((double)sampleX, (double)sampleZ, 0) * 2 - 1;
            if (perlinValue > threshold) {
                int y = chunk->getHeightAt(x,z);
                if (y+1 < 16) { //TODO else get another chunk
                    chunk->setBlockAt({x, y + 1, z}, Blocks::GRASS->getId());
                }
            }
        }
    }
}