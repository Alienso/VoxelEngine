//
// Created by Alienson on 21.4.2024..
//

#include "LightSource.h"
#include "Global.h"

LightSource::LightSource(glm::vec3 pos, glm::vec3 color) : Entity(*Global::materialManager.getAsset(Materials::LIGHT),
                                                                  &Global::cubeVertices[0], Global::cubeVertices.size()),
                                                           pos(pos), color(color) {
}

void LightSource::onUpdate(float deltaTime) {
    Entity::onUpdate(deltaTime);
}

void LightSource::render() {
    material.texture.bind();
    material.shader.use();
    bufferData.va->bind();

    glm::mat4 model= Global::currentFrame.model;

    material.shader.setMat4("projection", Global::currentFrame.projection);
    material.shader.setMat4("view", Global::currentFrame.view);
    material.shader.setMat4("model", glm::translate(model, pos));

    material.shader.setVec3("lightColor", color);

    glDrawArrays(GL_TRIANGLES, 0, 36); //@DANGER
}
