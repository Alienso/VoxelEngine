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
    shadowShader = Global::shaderManager.getAsset(Shaders::SHADOW);
}

void World::onRender() {

    Global::currentFrame.projection = glm::perspective(glm::radians(Configuration::fov), (float)Configuration::wWidth/(float)Configuration::wHeight,
                                                       0.01f, 1000.0f);
    Global::currentFrame.view = glm::lookAt(Global::camera.pos, Global::camera.pos + Global::camera.front, Global::camera.up);
    Global::currentFrame.model = glm::mat4(1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //renderShadows();

    //glViewport(0, 0, Configuration::wWidth,  Configuration::wHeight);
    renderScene();

    //Util::renderTexture(shadowBuffer.getTextureId());
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

    for(auto& e : entities)
        e.onUpdate(deltaTime);

    handleCollision();
    updateTerrain();
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
    float near_plane = 1.0f, far_plane = 7.5f;
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
    shadowShader->setMat4("model", glm::mat4(1.0f));

    renderScene();
    shadowBuffer.unbind();
}

void World::updateTerrain() {
    glm::ivec3 pos = Chunk::worldToChunkPos(Global::camera.pos.x, Global::camera.pos.y, Global::camera.pos.z);
    int renderDistance = Global::renderDistance;
    std::vector<Chunk*> newChunks;
    std::vector<Chunk*> chunksToRemove;
    std::vector<Chunk*> traversedChunks;
    for (int x = pos.x - renderDistance; x<=pos.x + renderDistance; x++){
        for (int z = pos.z - renderDistance; z<=pos.z + renderDistance; z++){
            if ((x - pos.x)*(x - pos.x) + (z - pos.z)*(z - pos.z) <= renderDistance * renderDistance){
                Chunk* chunk = chunkProvider.getChunkAt(x,0,z);
                if (chunk == nullptr){
                    chunk = chunkProvider.generateChunkAt(x,0,z);
                    newChunks.push_back(chunk);
                }
                traversedChunks.push_back(chunk);
            }
        }
    }

    bool found;
    for(const auto& it : chunkProvider.getChunks()){
        glm::ivec3 chunkPos = it.second->pos;
        found = false;
        for (auto c : traversedChunks){
            if (c->pos == chunkPos)
                found = true;
        }
        if (!found)
            chunksToRemove.push_back(it.second);
    }

    if (!newChunks.empty()){
        cullMesher.updateMeshes(newChunks, chunksToRemove, terrainMeshes, chunkProvider);
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

World::~World() {
    for (auto& it : terrainMeshes){
        delete it.second;
    }
    terrainMeshes.clear();
}
