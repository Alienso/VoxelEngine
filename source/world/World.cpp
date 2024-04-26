//
// Created by Alienson on 20.4.2024..
//

#include "World.h"
#include "InputHandler.h"
#include "Configuration.h"
#include "Blocks.h"
#include "Global.h"

#include "imgui/imgui.h"
#include "glm/ext/matrix_clip_space.hpp"


World::World() {
    cullMesher.generateMeshes(terrainMeshes, chunkProvider);
    //shadowShader = Global::shaderManager.getAsset(Shaders::SHADOW);
}

void World::onRender() {

    Global::currentFrame.projection = glm::perspective(glm::radians(Configuration::fov), (float)Configuration::wWidth/(float)Configuration::wHeight,
                                                       0.01f, 1000.0f);
    Global::currentFrame.view = glm::lookAt(Global::camera.pos, Global::camera.pos + Global::camera.front, Global::camera.up);
    Global::currentFrame.model = glm::mat4(1.0f);

    //renderShadows();

    //scene render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glViewport(0, 0, Configuration::wWidth,  Configuration::wHeight);
    renderScene();

    //Util::renderTexture(1);
}

void World::renderScene() {
    Global::sun->render();
    renderTerrain();
    Global::skybox->render();
}

void World::renderTerrain() {
    for (auto& it : terrainMeshes){
        Block& block = Blocks::getById(it.first);
        Mesh* mesh = it.second;
        mesh->render(block.getMaterial());
    }
}

void World::onUpdate(float deltaTime) {
    InputHandler::processKeyboardInput(deltaTime);
    InputHandler::processMouseInput();

    handleCollision();
}

void World::onImGuiRender() {
    ImGui::Begin("Hello, world!");

    ImGui::Text("camera pos= %f,%f,%f", Global::camera.pos[0], Global::camera.pos[1], Global::camera.pos[2]);
    ImGui::Text("pitch= %f, yaw = %f", Global::camera.pitch, Global::camera.yaw);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::SliderFloat3("LightPos", &Global::sun->pos.x, -5, 5);
    ImGui::SliderFloat3("LightColor", &Global::sun->color.x, 0, 1);

    ImGui::Text("Map height= %d", currentTerrainHeight);

    ImGui::End();
}

void World::renderShadows() {
    /*float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
                                      glm::vec3( 0.0f, 0.0f,  0.0f),
                                      glm::vec3( 0.0f, 1.0f,  0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    //shadow render
    glViewport(0, 0, Configuration::shadowWidth,  Configuration::shadowWidth);
    shadowBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);

    shadowShader->use();
    shadowShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

    renderScene();
    shadowBuffer.unbind();*/
}

void World::handleCollision() {
    //TODO this doesn't work
    /*glm::vec3 pos = Global::camera.pos;
    glm::i32vec3 chunkPos = { (int)floor(pos.x / 16.0), (int)floor(pos.y / 16.0), (int)floor(pos.z / 16.0) };
    glm::vec3 posInChunk = { abs((int)round(pos.x) % 16), abs((int)round(pos.y) % 16), abs((int)round(pos.z) % 16) };
    if (const auto& it = chunkMap.find(chunkPos); it != chunkMap.end()){
        Chunk* chunk = it->second;
        int index = (int)posInChunk.z * 16 + (int)posInChunk.x;
        if ((int)pos.y - 3 < chunk->heightMap[index]){
            Global::camera.pos.y = (float)chunk->heightMap[index] + 3;
        }
        currentTerrainHeight = chunk->heightMap[index];
    }else{

    }*/
}
