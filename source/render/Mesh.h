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
    float ao;

    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCoord, float ao) : pos(pos), normal(normal), texCoord(texCoord), ao(ao){}
};

class Mesh {
public:
    Mesh() = default;
    ~Mesh();
    static Mesh* fromRawData(float* vertices, size_t length);

    void bindVertexArray() const;
    void render(const Material& material);

    [[nodiscard]] size_t getVerticesCount() const;

private:
    std::vector<Vertex> vertices;
    BufferData* bufferData = nullptr;
};


#endif //VOXEL_MESH_H
