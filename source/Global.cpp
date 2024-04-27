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
    sun = new LightSource(glm::vec3{0,20,0},glm::vec3{1,1,1});
    skybox = new Skybox();
}

size_t Global::cubeVerticesSideSize = 48;

std::vector<size_t> Global::cubeVerticesSideOffsets = { //TODO
        0, cubeVerticesSideSize, 2*cubeVerticesSideSize, 3*cubeVerticesSideSize, 4*cubeVerticesSideSize, 5*cubeVerticesSideSize
};

std::vector<float> Global::cubeVertices =  {
        0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, //N
        1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
        0.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,

        0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, //S
        1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        0.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

        0.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, //L
        0.0f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        0.0f, 0.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        0.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

        1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, //R
        1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        1.0f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        1.0f, 0.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, //D
        1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 0.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
        1.0f, 0.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
        0.0f, 0.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

        0.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, //U
        1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        0.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        0.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f

};
