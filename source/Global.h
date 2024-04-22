//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_GLOBAL_H
#define INC_3DTEST_GLOBAL_H


#include <GLFW/glfw3.h>
#include "core/render/Camera.h"

#include "core/render/AssetManager.h"
#include "core/render/Texture.h"
#include "core/render/Material.h"

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

    static AssetManager<Texture> textureManager;
    static AssetManager<Material> materialManager;
    static AssetManager<Shader> shaderManager;

    static float cubeVertices[288];
};


#endif //INC_3DTEST_GLOBAL_H
