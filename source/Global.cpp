//
// Created by Alienson on 28.5.2023..
//

#include "Global.h"
#include "world/World.h"

#include <GLFW/glfw3.h>

SunEntity* Global::sun = nullptr;
Skybox* Global::skybox = nullptr;

void Global::init() {
    sun = new SunEntity(glm::vec3{0, 9999, 0});
    skybox = new Skybox();
}


GLFWwindow* Global::window;
Camera Global::camera;
CurrentFrame Global::currentFrame;
World* Global::world;

AssetManager<Texture> Global::textureManager;
AssetManager<Material> Global::materialManager;
AssetManager<Shader> Global::shaderManager;