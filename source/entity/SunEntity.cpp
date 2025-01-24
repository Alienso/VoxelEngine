//
// Created by Alienson on 21.4.2024..
//

#include "SunEntity.h"
#include "Global.h"
#include "CubeVerticesTypes.h"
#include "world/World.h"
#include "Configuration.h"
#include "glm/ext/matrix_clip_space.inl"

#include <GLFW/glfw3.h>

SunEntity::SunEntity(glm::vec3 pos) : Entity(*Global::materialManager.getAsset(Materials::LIGHT),
                                                              &CubeVerticesTypes::cubeVerticesSingle[0], CubeVerticesTypes::cubeVerticesSingle.size()), pos(pos) {
}

void SunEntity::onUpdate(float deltaTime) {
    Entity::onUpdate(deltaTime);
    pos = getLightDir() * glm::vec3(9999);
}

void SunEntity::render() {
    material.texture.bind();
    material.shader.use();
    bufferData.va->bind();

    glm::mat4 model= Global::currentFrame.model;

    glm::mat4 projection = Global::currentFrame.projection = glm::perspective(glm::radians(GraphicsConfiguration::fov), (float)Configuration::windowWidth / (float)Configuration::windowHeight,
                                                                              1.0f, 100000.0f);

    //TODO FIX THIS RENDER
    material.shader.setMat4("projection", projection);
    material.shader.setMat4("view", Global::currentFrame.view);
    material.shader.setMat4("model", glm::translate(model, pos) * glm::scale(model, glm::vec3(1000.0f, 1000.0f, 1000.0f))); //TODO dont calculate all of this every frame

    material.shader.setVec3("lightColor", getColor() * lightStrength);
    /*material.shader.setVec3("lightCenter", pos);
    material.shader.setVec2("uResolution", glm::vec2(Configuration::wWidth, Configuration::wHeight));*/

    glDrawArrays(GL_TRIANGLES, 0, 36); //@DANGER
}

glm::vec3 SunEntity::getColor() const {
    /*
     * r: 255 | 255 | 255 | 252 | 250 | 250 | 250
     * g: 255 | 245 | 228 | 204 | 176 | 170 | 134
     * b: 255 | 123 | 105 | 81  | 51  | 27  | 7
     */
    float t = (2 * (float)World::getTimeOfDay() / 86400.0f) - 1; //max 86400 [-1,1]
    float r = 1.0f;
    float g = 1.0f - 0.47f * powf(t,16);
    float b = 1.0f - 0.97f * powf(t,16);
    return {r,g,b};
}

glm::vec3 SunEntity::getLightDir() const {
    // 1,0 -> 0,1 -> -1,0 -> 0,-1 //TODO make sun go down
    // x*x + y*y = 1;
    float t = (float)World::getTimeOfDay() / 86400.0f; //max 86400
    float x = 1 - 2*t;
    float y = sqrtf(1 - x*x);
    return {x,y,0.2};
}
