//
// Created by Alienson on 3.5.2024..
//

#include "Biome.h"
#include "world/ChunkProvider.h"
#include "world/Chunk.h"

void Biome::decorateChunk(Chunk *chunk, ChunkProvider& chunkProvider) {
    plantGenerator.decorate(chunk);
    treeGenerator.decorate(chunk, chunkProvider);
    waterGen.decorate(chunk, chunkProvider);
    chunk->isDecorated = true;
}