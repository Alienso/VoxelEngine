//
// Created by Alienson on 21.4.2024..
//

#include "Mesh.h"
#include "Global.h"
#include "render/buffer/BufferData.h"
#include "world/World.h"

#include <GLFW/glfw3.h>
#include <mutex>

Mesh::~Mesh() {
    Global::world->deleteBufferData(bufferData);
}

Mesh *Mesh::fromRawData(float *vertexData, size_t length) {
    Mesh* mesh = new Mesh();
    mesh->vertices.reserve(length / 9);
    for (size_t i = 0; i < length; i+=9){
        mesh->vertices.emplace_back(glm::vec3{vertexData[i], vertexData[i+1], vertexData[i+2]},
                                    glm::vec3{vertexData[i+3], vertexData[i+4], vertexData[i+5]},
                                    glm::vec2{vertexData[i+6], vertexData[i+7]}, vertexData[i+8]);
    }
    //mesh->bufferData = BufferData(vertexData, length);
    //memcpy((void*)&(mesh->vertices[0]), (void*)vertexData, length); //TODO alignment?

    std::mutex mut;
    std::unique_lock<std::mutex> lock(mut);
    std::condition_variable cv;
    mesh->bufferData = new BufferData();
    Global::world->genBufferData(vertexData, length, mesh->bufferData, cv);
    cv.wait(lock);
    //mut.lock();

    return mesh;
}

void Mesh::render(const Material &material) {
    material.texture.bind();
    material.shader.use();
    bufferData->va->bind();

    material.shader.setMat4("projection", Global::currentFrame.projection);
    material.shader.setMat4("view", Global::currentFrame.view);
    material.shader.setMat4("model", Global::currentFrame.model);

    material.shader.setVec3("lightColor", Global::sun->getColor());
    material.shader.setVec3("lightDir", Global::sun->getLightDir());
    material.shader.setVec3("viewPos", Global::camera.pos);

    material.shader.setFloat("ambientStrength", material.ambientStrength);
    material.shader.setFloat("specularStrength", material.specularStrength);
    material.shader.setInt("shininess", material.shininess);


    glDrawArrays(GL_TRIANGLES, 0, (int)vertices.size()); //@Danger
}

size_t Mesh::getVerticesCount() const {
    return vertices.size();
}

void Mesh::bindVertexArray() const {
    bufferData->va->bind();
}
