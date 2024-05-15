//
// Created by Alienson on 3.5.2024..
//

#include "TreeGenerator.h"
#include "world/Blocks.h"
#include "world/ChunkProvider.h"

TreeGenerator::TreeGenerator(){
    scale = 0.9f;
    threshold = 0.6f;
}

void TreeGenerator::decorate(Chunk *chunk, ChunkProvider& chunkProvider) {
    for (int x = 0; x<Chunk::CHUNK_SIZE; x++){
        for (int z = 0; z<Chunk::CHUNK_SIZE; z++){
            float sampleX = (float)(x + chunk->x * Chunk::CHUNK_SIZE) * scale;
            float sampleZ = (float)(z + chunk->z * Chunk::CHUNK_SIZE) * scale;
            float perlinValue = (float)perlinNoise.noise((double)sampleX, (double)sampleZ, 0) * 2 - 1;
            if (perlinValue > threshold) {
                int y = chunk->getHeightAt(x,z);
                glm::vec3 pos = chunk->chunkToWorldPos(x,y,z);
                pos.y+=1;
                generateTree(pos, chunkProvider);
            }
        }
    }
}

void TreeGenerator::generateTree(glm::vec3 pos, ChunkProvider& chunkProvider) {

    int height = 6 + (rand() * 100) % 3;
    for (int i=0; i<height; i++){
        //leaves
        if (i > height / 2){
            for (int x=-3;x<=3;x++){
                for (int z=-3;z<=3;z++){
                    chunkProvider.setBlockAtWorldPos(pos.x + x, pos.y + i, pos.z + z, Blocks::OAK_LEAVES->getId());
                }
            }
        }
        //trunk
        chunkProvider.setBlockAtWorldPos(pos.x, pos.y + i, pos.z, Blocks::OAK_WOOD->getId());
    }

    //Top
    for (int x=-1;x<=1;x++){
        for (int z=-1;z<=1;z++){
            chunkProvider.setBlockAtWorldPos(pos.x + x, pos.y + height, pos.z + z, Blocks::OAK_LEAVES->getId());
        }
    }

}
