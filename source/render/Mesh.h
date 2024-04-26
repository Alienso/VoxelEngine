//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_MESH_H
#define VOXEL_MESH_H

#include "glm/glm.hpp"
#include "Material.h"
#include "render/buffer/BufferData.h"

#include <vector>

class BufferData;

struct Vertex{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;

    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCoord) : pos(pos), normal(normal), texCoord(texCoord){}
};

class Mesh {
public:
    Mesh() = default;
    static Mesh* fromRawData(float* vertices, size_t length);

    void render(const Material& material);

private:
    std::vector<Vertex> vertices;
    BufferData bufferData;
};


#endif //VOXEL_MESH_H
