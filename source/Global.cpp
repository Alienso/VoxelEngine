//
// Created by Alienson on 28.5.2023..
//

#include "Global.h"

SunEntity* Global::sun = nullptr;
Skybox* Global::skybox = nullptr;

void Global::init() {
    sun = new SunEntity(glm::vec3{0, 50, 0});
    skybox = new Skybox();
}


GLFWwindow* Global::window = nullptr;
Camera Global::camera;
CurrentFrame Global::currentFrame;

AssetManager<Texture> Global::textureManager;
AssetManager<Material> Global::materialManager;
AssetManager<Shader> Global::shaderManager;

int Global::renderDistance = 12;