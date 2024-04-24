//
// Created by Alienson on 28.5.2023..
//

#include "Global.h"

GLFWwindow* Global::window = nullptr;
Camera Global::camera;
CurrentFrame Global::currentFrame;

AssetManager<Texture> Global::textureManager;
AssetManager<Material> Global::materialManager;
AssetManager<Shader> Global::shaderManager;

LightSource* Global::sun = nullptr;
Skybox* Global::skybox = nullptr;

void Global::init() {
    sun = new LightSource(glm::vec3{1,10,1},glm::vec3{1,1,1});
    skybox = new Skybox();
}

float Global::cubeVertices[288] =  {
        0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
        0.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,

        0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        0.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

        0.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        0.0f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        0.0f, 0.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        0.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

        1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        1.0f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        1.0f, 0.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 0.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
        1.0f, 0.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
        0.0f, 0.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

        0.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        0.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        0.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f

};
