//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_GLOBAL_H
#define INC_3DTEST_GLOBAL_H


#include <GLFW/glfw3.h>
#include "render/Camera.h"

#include "render/AssetManager.h"
#include "render/Texture.h"
#include "render/Material.h"
#include "entity/LightSource.h"
#include "entity/Skybox.h"

#include <vector>

struct CurrentFrame{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    CurrentFrame() : model(glm::identity<glm::mat4>()), view(glm::identity<glm::mat4>()), projection(glm::identity<glm::mat4>()) {}
};

class Global {
public:
    static GLFWwindow* window;
    static Camera camera;
    static CurrentFrame currentFrame;
    static LightSource* sun;
    static Skybox* skybox;

    static AssetManager<Texture> textureManager;
    static AssetManager<Material> materialManager;
    static AssetManager<Shader> shaderManager;

    static std::vector<float> cubeVertices;
    static std::vector<size_t> cubeVerticesSideOffsets;
    static size_t cubeVerticesSideSize;

public:
    static void init();
};


#endif //INC_3DTEST_GLOBAL_H
