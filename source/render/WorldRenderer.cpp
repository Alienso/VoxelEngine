//
// Created by Alienson on 30.4.2024..
//

#include "WorldRenderer.h"
#include "world/Block.h"
#include "world/Blocks.h"
#include "glm/glm.hpp"
#include "Configuration.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "Global.h"

#include <GLFW/glfw3.h>

WorldRenderer::WorldRenderer() {
    //shadowShader = Global::shaderManager.getAsset(Shaders::SHADOW);
}

WorldRenderer::~WorldRenderer() {
    for (auto& it : terrainMeshes){
        delete it.second;
    }
    terrainMeshes.clear();
}

void WorldRenderer::renderScene() {

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //renderFog();
    Global::sun->render();

    //DepthMap gen
    /*depthBuffer.bind();
    renderTerrain();
    depthBuffer.unbind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/

    renderTerrain();

    //Util::renderTexture(depthBuffer.getTextureId());
    Global::skybox->render();

    glDisable(GL_DEPTH_TEST);
}

void WorldRenderer::renderTerrain() {
    for (auto& it : terrainMeshes){
        Block& block = Blocks::getById(it.first);
        Mesh* mesh = it.second;
        renderBlockMesh(block, mesh);
        //mesh->render(block.getMaterial());
    }
}

void WorldRenderer::renderShadows() {
    float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
                                      glm::vec3( 0.0f, 0.0f,  0.0f),
                                      glm::vec3( 0.0f, 1.0f,  0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    //shadow render
    glViewport(0, 0, Configuration::shadowWidth,  Configuration::shadowWidth);
    depthBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);

    shadowShader->use();
    shadowShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    shadowShader->setMat4("model", glm::mat4(1.0f));

    //renderScene();
    depthBuffer.unbind();
}

std::unordered_map<uint16_t, Mesh *>& WorldRenderer::getTerrainMeshes() {
    return terrainMeshes;
}

void WorldRenderer::renderBlockMesh(Block &block, Mesh *mesh) {
    Shader& shader = block.getMaterial().shader;
    block.getMaterial().texture.bind();
    shader.use();
    mesh->bindVertexArray();

    shader.setMat4("projection", Global::currentFrame.projection);
    shader.setMat4("view", Global::currentFrame.view);
    shader.setMat4("model", Global::currentFrame.model);
    shader.setFloat("uTime", (float)glfwGetTime());

    shader.setVec3("lightColor", Global::sun->getColor());
    shader.setVec3("lightDir", Global::sun->getLightDir());
    shader.setVec3("viewPos", Global::camera.pos);

    shader.setFloat("ambientStrength", block.getMaterial().ambientStrength);
    shader.setFloat("specularStrength", block.getMaterial().specularStrength);
    shader.setInt("shininess", block.getMaterial().shininess);

    glDrawArrays(GL_TRIANGLES, 0, (int)mesh->getVerticesCount()); //@Danger
}

void WorldRenderer::renderFog() {
    //fogBuffer.bind();
}
