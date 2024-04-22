//
// Created by Alienson on 20.4.2024..
//

#include "World.h"
#include "../../InputHandler.h"
#include "../../Configuration.h"
#include "Blocks.h"

#include <imgui/imgui.h>
#include "glm/ext/matrix_clip_space.hpp"

World::World() {
    chunkMap[{0,0,0}] = new Chunk(0,0,0);
    lightSources.emplace_back(glm::vec3{1,1,1},glm::vec3{1,1,1});
    terrainMeshes[1] = Mesh::fromRawData(Global::cubeVertices, sizeof(Global::cubeVertices));
}

World::~World() {
    for (auto it : chunkMap){
        delete it.second;
    }
}

void World::onRender() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Global::currentFrame.projection = glm::perspective(glm::radians(Configuration::fov), (float)Configuration::wWidth/(float)Configuration::wHeight,
                                            0.01f, 1000.0f);
    Global::currentFrame.view = glm::lookAt(Global::camera.pos, Global::camera.pos + Global::camera.front, Global::camera.up);
    Global::currentFrame.model = glm::mat4(1.0f);

    lightSources[0].render();
    renderTerrain();

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
}

void World::onImGuiRender() {
    ImGui::Begin("Hello, world!");

    ImGui::Text("camera pos= %f,%f,%f", Global::camera.pos[0], Global::camera.pos[1], Global::camera.pos[2]);
    ImGui::Text("pitch= %f, yaw = %f", Global::camera.pitch, Global::camera.yaw);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::SliderFloat3("LightPos", &lightSources[0].pos.x, -5, 5);
    ImGui::SliderFloat3("LightColor", &lightSources[0].color.x, 0, 1);
    ImGui::SliderInt("Shininess", &shininess, 0, 64);
    ImGui::SliderFloat("AmbientStrength", &ambientStrength, 0, 1);
    ImGui::SliderFloat("SpecularStrength", &specularStrength, 0, 1);

    ImGui::End();
}

Chunk &World::getChunk(int x, int y, int z) {
    if (auto it = chunkMap.find({x,y,z}); it != chunkMap.end()){
        return *it->second;
    }
    //generate chunk and return it; maybe it is generated but not loaded?
    auto* chunk = new Chunk(x,y,z);
    chunkMap[{x,y,z}] = chunk;
    return *chunk;
}
