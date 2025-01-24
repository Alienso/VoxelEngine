//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_GLOBAL_H
#define INC_3DTEST_GLOBAL_H

#include "render/Camera.h"

#include "render/AssetManager.h"
#include "render/Texture.h"
#include "render/Material.h"
#include "entity/SunEntity.h"
#include "entity/Skybox.h"

#include <vector>

class World;
class GLFWwindow;

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
    static SunEntity* sun;
    static Skybox* skybox;
    static World* world;

    static AssetManager<Texture> textureManager;
    static AssetManager<Material> materialManager;
    static AssetManager<Shader> shaderManager;

public:
    static void init();
};


#endif //INC_3DTEST_GLOBAL_H
