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

int World::timeOfDay = 5000;

World::World() {
    updateTerrain();
    cullMesher.generateMeshes(worldRenderer.getTerrainMeshes(), chunkProvider);
}

void World::onRender() {

    Global::currentFrame.projection = glm::perspective(glm::radians(Configuration::fov), (float)Configuration::wWidth/(float)Configuration::wHeight,
                                                       1.0f, (float)(Global::renderDistance + 1)*Chunk::CHUNK_SIZE);
    Global::currentFrame.view = glm::lookAt(Global::camera.pos, Global::camera.pos + Global::camera.front, Global::camera.up);
    Global::currentFrame.model = glm::mat4(1.0f);

    //glViewport(0, 0, Configuration::wWidth,  Configuration::wHeight);
    worldRenderer.renderScene();
    //Util::renderTexture(shadowBuffer.getTextureId());
}

void World::onUpdate(float deltaTime) {
    InputHandler::processKeyboardInput(deltaTime);
    InputHandler::processMouseInput();

    for(auto& e : entities)
        e.onUpdate(deltaTime);

    handleCollision();
    updateTerrain();

    //timeOfDay = (timeOfDay + 1)  % 86400;
}

void World::onImGuiRender() {
    ImGui::Begin("Hello, world!");

    ImGui::Text("camera pos= %f,%f,%f", Global::camera.pos[0], Global::camera.pos[1], Global::camera.pos[2]);
    ImGui::Text("pitch= %f, yaw = %f", Global::camera.pitch, Global::camera.yaw);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::SliderFloat3("SunPos", &Global::sun->pos.x, -5, 5);
    ImGui::SliderFloat3("SunColor", &Global::sun->color.x, 0, 1);
    ImGui::SliderInt("TimeOfDay", &timeOfDay, 0, 86400);

    ImGui::Text("Map height= %d", currentTerrainHeight);

    ImGui::End();
}

void World::updateTerrain() {
    bool newChunks = false;
    glm::ivec3 pos = Chunk::worldToChunkPos(Global::camera.pos.x, Global::camera.pos.y, Global::camera.pos.z);
    int renderDistance = Global::renderDistance;
    std::vector<Chunk*> chunksToRemove;
    std::vector<Chunk*> traversedChunks;
    for (int x = pos.x - renderDistance; x<=pos.x + renderDistance; x++){
        for (int z = pos.z - renderDistance; z<=pos.z + renderDistance; z++){
            if ((x - pos.x)*(x - pos.x) + (z - pos.z)*(z - pos.z) <= renderDistance * renderDistance){
                Chunk* chunk = chunkProvider.getChunkAt(x,0,z);
                if (chunk == nullptr){
                    chunk = chunkProvider.generateChunkAt(x,0,z);
                    newChunks = true;
                }
                traversedChunks.push_back(chunk);
            }
        }
    }

    //If there are new chunks there are probably chunks to be removed
    if (newChunks) {
        bool found;
        for (const auto &it: chunkProvider.getChunks()) {
            glm::ivec3 chunkPos = it.second->pos;
            found = false;
            for (auto c: traversedChunks) {
                if (c->pos == chunkPos)
                    found = true;
            }
            if (!found)
                chunksToRemove.push_back(it.second);
        }
    }

    if (!chunksToRemove.empty()){
        cullMesher.updateMeshes(chunksToRemove, worldRenderer.getTerrainMeshes(), chunkProvider);
    }
}

void World::handleCollision() {
    glm::vec3 pos = Global::camera.pos;
    Chunk* chunk = chunkProvider.getChunkAtWorldPos(pos.x, pos.y, pos.z);
    if (chunk == nullptr)
        return;
    glm::uvec3 posInChunk = Chunk::getRelativeChunkPos(pos);
    int height = chunk->getHeightAt((int)posInChunk.x, (int)posInChunk.z);
    if ((int)pos.y - 3 < height){
        Global::camera.pos.y = (float)height + 3;
    }
    currentTerrainHeight = height;
}

int World::getTimeOfDay() {
    return timeOfDay;
}
