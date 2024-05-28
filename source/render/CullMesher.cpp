//
// Created by Alienson on 23.4.2024..
//

#include <chrono>
#include "CullMesher.h"
#include "world/Blocks.h"
#include "CubeVerticesTypes.h"

#include "world/ChunkProvider.h"

struct genInfo{
    glm::ivec3 pos;
    uint16_t block;

    genInfo(glm::ivec3 pos_, uint16_t block_) : pos(pos_), block(block_){}
};

CullMesher::CullMesher() {}


void CullMesher::generateMeshes(terrainMeshMap &terrainMeshes, ChunkProvider &chunkProvider) {

    /*std::cout << "verticesForBlockChunkMap size=" << verticesForBlockChunkMap.size() << '\n';
    std::cout << "Chunk size=" << chunkProvider.getChunks().size() << '\n';
    Timer generatingVertices("Generating vertices");*/

    std::vector<genInfo> newChunks;

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
                            newChunks.emplace_back(chunk->pos, blockId);
                        }
                    }
                }
            }
        }
    }

    //generatingVertices.stop();
    //Timer timer("Generating mesh");

    for (auto &chunk : verticesForBlockChunkMap){
        for (auto &blockVertices : chunk.second) {
            auto it = terrainMeshes.find(blockVertices.first);
            if (it == terrainMeshes.end()){
                terrainMeshes.insert(std::make_pair(blockVertices.first, std::unordered_map<glm::ivec3, Mesh*, GlmVec3Functions, GlmVec3Functions>()));
            }
            it = terrainMeshes.find(blockVertices.first);
            if (it->second.find(chunk.first) == it->second.end()){
                terrainMeshes[blockVertices.first].insert(std::make_pair(chunk.first, Mesh::fromRawData((float*) (&(blockVertices.second[0])), blockVertices.second.size() * 9)));
            }
        }
    }

    //mapTransform.stop();
    //std::cout << "----------------------------------\n";
}

void CullMesher::updateMeshes(const std::vector<Chunk *> &chunksToRemove, terrainMeshMap& terrainMeshes, ChunkProvider& chunkProvider) {

    for(Chunk* chunk : chunksToRemove){
        if (verticesForBlockChunkMap.find(chunk->pos) != verticesForBlockChunkMap.end()){
            verticesForBlockChunkMap.erase(chunk->pos);
            for (auto blockMesh : terrainMeshes) {
                auto it = blockMesh.second.find(chunk->pos);
                if (it == blockMesh.second.end()) {
                    continue;
                }
                //delete it->second; //There is some issue that makes the current rendering VBO to be deleted
                //blockMesh.second.clear();
            }
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
            if ((otherBlock.isTransparent() || block.isTransparent()) && otherBlock.getId() != block.getId()) { //TODO add if we should merge blocks into blob or not
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

    for (size_t i = 0; i < CubeVerticesTypes::cubeVerticesSideSize; i+=9) { //TODO memcpy?
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
    //verticesForBlockChunkMap.erase(chunk->pos); //TODO
}
