//
// Created by Alienson on 23.4.2024..
//

#include <chrono>
#include "CullMesher.h"
#include "world/Blocks.h"
#include "CubeVerticesTypes.h"

CullMesher::CullMesher() {}


void CullMesher::generateMeshes(std::unordered_map<uint16_t, Mesh *> &terrainMeshes, ChunkProvider &chunkProvider) {

    Mesh* currentMesh;
    verticesForBlockMap.clear();

    /*std::cout << "verticesForBlockChunkMap size=" << verticesForBlockChunkMap.size() << '\n';
    std::cout << "Chunk size=" << chunkProvider.getChunks().size() << '\n';
    Timer timer("Generating mesh");
    Timer generatingVertices("Generating vertices");*/

    for (auto& it : chunkProvider.getChunks()){
        Chunk* chunk = it.second;
        if (verticesForBlockChunkMap.find(chunk->pos) == verticesForBlockChunkMap.end()) {
            for (int y = 0; y < Chunk::CHUNK_SIZE; y++) {
                for (int x = 0; x < Chunk::CHUNK_SIZE; x++) {
                    for (int z = 0; z < Chunk::CHUNK_SIZE; z++) {
                        auto blockId = chunk->getBlockAt(x, y, z);
                        if (blockId != Blocks::AIR->getId()) {
                            Block& block = Blocks::getById(blockId);
                            generateVerticesForBlockChunk(*chunk, block, {x, y, z}, chunkProvider);
                        }
                    }
                }
            }
        }
    }

    //generatingVertices.stop();
    //Timer mapTransform("Map Transform");

    //TODO optimize this!
    for (const auto& it : verticesForBlockChunkMap){
        for (const auto& blockMap : it.second){
            for (const auto& v : blockMap.second) {
                verticesForBlockMap[blockMap.first].push_back(v);
            }
        }
    }

    //mapTransform.stop();
    //Timer final("Final");

    for (const auto& it : verticesForBlockMap) {
        if (it.second.empty())
            continue;
        currentMesh = Mesh::fromRawData((float *) (&(it.second[0])), it.second.size() * 9);
        if (auto meshIter = terrainMeshes.find(it.first); meshIter != terrainMeshes.end()) {
            delete meshIter->second;
        }
        terrainMeshes[it.first] =  currentMesh;
    }

    //final.stop();
    //std::cout << "----------------------------------\n";
}

void CullMesher::updateMeshes(const std::vector<Chunk *> &chunksToRemove, std::unordered_map<uint16_t, Mesh *>& terrainMeshes, ChunkProvider& chunkProvider) {

    for(Chunk* chunk : chunksToRemove){
        if (verticesForBlockChunkMap.find(chunk->pos) != verticesForBlockChunkMap.end()){
            verticesForBlockChunkMap.erase(chunk->pos);
        }
        chunkProvider.deleteChunkAt(chunk->pos);
    }

    generateMeshes(terrainMeshes, chunkProvider);
}

void CullMesher::generateVerticesForBlockChunk(const Chunk &chunk, const Block& block, const glm::ivec3 posInChunk, ChunkProvider& chunkProvider) {

    glm::ivec3 posOffset = posInChunk + glm::ivec3(chunk.x * Chunk::CHUNK_SIZE, chunk.y * Chunk::CHUNK_SIZE,
                                                   chunk.z * Chunk::CHUNK_SIZE);

    if (block.isRegularBlock()) {
        for (auto side: EnumFacing::sides) {
            Block &otherBlock = getAdjacentBlock(const_cast<Chunk *>(&chunk), posInChunk, side, chunkProvider);
            if ((otherBlock.getId() == block.getId()) && otherBlock.shouldNeverRenderSides()){
                continue;
            }
            else if (otherBlock.isTransparent()) {
                addVerticesForSide(block, posOffset, side, chunk, chunkProvider);
            }
        }
    }else{
        for (auto side: EnumFacing::sides) {
            Block &otherBlock = getAdjacentBlock(const_cast<Chunk *>(&chunk), posInChunk, side, chunkProvider);
            if (otherBlock.isTransparent()) {
                addVertices(block, posOffset, chunk, chunkProvider);
                break;
            }
        }
    }
}
void CullMesher::addVertices(const Block& block, glm::ivec3 posOffset, const Chunk& chunk, ChunkProvider& chunkProvider){
    size_t cubeDataSize = block.getVerticesPtr()->size();
    float* cubeData = &((*block.getVerticesPtr())[0]);

    for (size_t i = 0; i < cubeDataSize; i+=9){ //TODO memcpy?
        float ao = getAOValue(i/9, 0, &cubeData[i], chunkProvider); //TODO 0?
        verticesForBlockChunkMap[chunk.pos][block.getId()].emplace_back(glm::vec3{cubeData[i] + (float)posOffset.x, cubeData[i + 1] + (float)posOffset.y, cubeData[i + 2] + (float)posOffset.z},
                                                                        glm::vec3{cubeData[i+3], cubeData[i+4], cubeData[i+5]},
                                                                        glm::vec2{cubeData[i+6], cubeData[i+7]}, ao);
    }
}

void CullMesher::addVerticesForSide(const Block& block, glm::ivec3 posOffset, const EnumFacing *side, const Chunk& chunk, ChunkProvider& chunkProvider) {
    size_t offset = CubeVerticesTypes::cubeVerticesSideOffsets[side->id]; //Danger have mapper?
    float* cubeData = &((*block.getVerticesPtr())[offset]);

    for (size_t i = 0; i < CubeVerticesTypes::cubeVerticesSideSize; i+=9){ //TODO memcpy?
        float ao = getAOValue(i/9, side->id, &cubeData[i], chunkProvider);
        verticesForBlockChunkMap[chunk.pos][block.getId()].emplace_back(glm::vec3{cubeData[i] + (float)posOffset.x, cubeData[i + 1] + (float)posOffset.y, cubeData[i + 2] + (float)posOffset.z},
                                                  glm::vec3{cubeData[i+3], cubeData[i+4], cubeData[i+5]},
                                                  glm::vec2{cubeData[i+6], cubeData[i+7]}, ao);
    }
}

Block& CullMesher::getAdjacentBlock(Chunk *chunk, glm::ivec3 posInChunk, const EnumFacing* side, const ChunkProvider &provider) {

    glm::ivec3 pos = posInChunk + side->dirVec;

    if (pos.x < 0 || pos.x >= Chunk::CHUNK_SIZE ||
        pos.y < 0 || pos.y >= Chunk::CHUNK_SIZE ||
        pos.z < 0 || pos.z >= Chunk::CHUNK_SIZE) {

        chunk = provider.getAdjacentChunk(*chunk, side);
        if (chunk == nullptr)
            return *Blocks::AIR;
        pos.x = (pos.x + Chunk::CHUNK_SIZE) % Chunk::CHUNK_SIZE;
        pos.y = (pos.y + Chunk::CHUNK_SIZE) % Chunk::CHUNK_SIZE;
        pos.z = (pos.z + Chunk::CHUNK_SIZE) % Chunk::CHUNK_SIZE;
    }

    return Blocks::getById(chunk->getBlockAt(pos));
}

void CullMesher::invalidateChunkCache(Chunk *chunk) {
    verticesForBlockChunkMap.erase(chunk->pos);
}
