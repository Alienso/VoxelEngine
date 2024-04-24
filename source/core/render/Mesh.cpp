//
// Created by Alienson on 21.4.2024..
//

#include "Mesh.h"
#include "../../Global.h"
#include "buffer/BufferData.h"

Mesh *Mesh::fromRawData(float *vertexData, size_t length) {
    Mesh* mesh = new Mesh();
    for (size_t i = 0; i < length; i+=8){
        mesh->vertices.emplace_back(glm::vec3{vertexData[i], vertexData[i+1], vertexData[i+2]},
                                    glm::vec3{vertexData[i+3], vertexData[i+4], vertexData[i+5]},
                                    glm::vec2{vertexData[i+6], vertexData[i+7]});
    }
    mesh->bufferData = BufferData(vertexData, length);
    return mesh;
}

void Mesh::render(const Material &material) {
    material.texture.bind();
    material.shader.use();
    bufferData.va->bind();

    glm::mat4 model = Global::currentFrame.model;

    material.shader.setMat4("projection", Global::currentFrame.projection);
    material.shader.setMat4("view", Global::currentFrame.view);
    material.shader.setMat4("model", model);

    material.shader.setInt("texture1", 0);

    material.shader.setVec3("lightColor", Global::sun->color);
    material.shader.setVec3("lightPos", Global::sun->pos);
    material.shader.setVec3("viewPos", Global::camera.pos);

    material.shader.setFloat("ambientStrength", material.ambientStrength);
    material.shader.setFloat("specularStrength", material.specularStrength);
    material.shader.setInt("shininess", material.shininess);


    glDrawArrays(GL_TRIANGLES, 0, (int)vertices.size()); //@Danger
}
