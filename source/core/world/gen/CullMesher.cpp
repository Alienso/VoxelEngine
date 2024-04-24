//
// Created by Alienson on 23.4.2024..
//

#include "CullMesher.h"
#include "Global.h"

void CullMesher::generateMeshes(std::unordered_map<uint16_t, Mesh *> &terrainMeshes,
                                std::unordered_map<glm::u32vec3, Chunk *, GlmVec3Functions, GlmVec3Functions> &chunkMap) {

    for (auto& it : chunkMap){
        Chunk* chunk = it.second;
        Mesh* currentMesh;
        std::vector<Vertex> vertices;
        for (int b=0; b<4096; b++){
            auto block = chunk->blocks[b];
            if (block != 0){
                float* cubeData = Global::cubeVertices;
                glm::vec3 posOffset = Chunk::posFromIndex(b);
                for (int i=0; i<288; i+=8){
                    vertices.emplace_back(glm::vec3{cubeData[i] + posOffset.x, cubeData[i+1] + posOffset.y, cubeData[i+2] + posOffset.z},
                                          glm::vec3{cubeData[i+3], cubeData[i+4], cubeData[i+5]},
                                          glm::vec2{cubeData[i+6], cubeData[i+7]});
                }
            }
        }

        if (vertices.empty())
            return;

        currentMesh = Mesh::fromRawData((float*)(&(vertices[0])), vertices.size() * 8);
        terrainMeshes[1] = currentMesh; //TODO, memory?

    }
}
