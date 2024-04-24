//
// Created by Alienson on 23.4.2024..
//

#include "Skybox.h"
#include "Global.h"

std::vector<const char*> Skybox::resourcePath = {"textures/skybox/right.png", "textures/skybox/left.png",
                                                 "textures/skybox/bottom.png", "textures/skybox/top.png",
                                                 "textures/skybox/front.png", "textures/skybox/back.png"};

Skybox::Skybox() : Entity(*Global::materialManager.getAsset(Materials::SKYBOX)) {
    std::vector<int> layout = {3};
    bufferData = BufferData(skyboxVertices, sizeof(skyboxVertices) / sizeof(float), layout);
}

void Skybox::onUpdate(float deltaTime) {
    Entity::onUpdate(deltaTime);
}

void Skybox::render() {

    glDepthFunc(GL_LEQUAL);

    material.texture.bindCubeMap();
    material.shader.use();
    bufferData.va->bind();

    glm::mat4 view = glm::mat4(glm::mat3(Global::camera.getViewMatrix()));

    material.shader.setMat4("projection", Global::currentFrame.projection);
    material.shader.setMat4("view", Global::currentFrame.view);

    glDrawArrays(GL_TRIANGLES, 0, 36); //@Danger

    glDepthFunc(GL_LESS);
}

float Skybox::skyboxVertices[108] = {
        // positions
        -10000000.0f,  10000000.0f, -10000000.0f,
        -10000000.0f, -10000000.0f, -10000000.0f,
        10000000.0f, -10000000.0f, -10000000.0f,
        10000000.0f, -10000000.0f, -10000000.0f,
        10000000.0f,  10000000.0f, -10000000.0f,
        -10000000.0f,  10000000.0f, -10000000.0f,

        -10000000.0f, -10000000.0f,  10000000.0f,
        -10000000.0f, -10000000.0f, -10000000.0f,
        -10000000.0f,  10000000.0f, -10000000.0f,
        -10000000.0f,  10000000.0f, -10000000.0f,
        -10000000.0f,  10000000.0f,  10000000.0f,
        -10000000.0f, -10000000.0f,  10000000.0f,

        10000000.0f, -10000000.0f, -10000000.0f,
        10000000.0f, -10000000.0f,  10000000.0f,
        10000000.0f,  10000000.0f,  10000000.0f,
        10000000.0f,  10000000.0f,  10000000.0f,
        10000000.0f,  10000000.0f, -10000000.0f,
        10000000.0f, -10000000.0f, -10000000.0f,

        -10000000.0f, -10000000.0f,  10000000.0f,
        -10000000.0f,  10000000.0f,  10000000.0f,
        10000000.0f,  10000000.0f,  10000000.0f,
        10000000.0f,  10000000.0f,  10000000.0f,
        10000000.0f, -10000000.0f,  10000000.0f,
        -10000000.0f, -10000000.0f,  10000000.0f,

        -10000000.0f,  10000000.0f, -10000000.0f,
        10000000.0f,  10000000.0f, -10000000.0f,
        10000000.0f,  10000000.0f,  10000000.0f,
        10000000.0f,  10000000.0f,  10000000.0f,
        -10000000.0f,  10000000.0f,  10000000.0f,
        -10000000.0f,  10000000.0f, -10000000.0f,

        -10000000.0f, -10000000.0f, -10000000.0f,
        -10000000.0f, -10000000.0f,  10000000.0f,
        10000000.0f, -10000000.0f, -10000000.0f,
        10000000.0f, -10000000.0f, -10000000.0f,
        -10000000.0f, -10000000.0f,  10000000.0f,
        10000000.0f, -10000000.0f,  10000000.0f
};
