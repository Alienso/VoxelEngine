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
#include "util/Util.h"
#include "glad.h"

#include <GLFW/glfw3.h>

WorldRenderer::WorldRenderer() {
    //shadowShader = Global::shaderManager.getAsset(Shaders::SHADOW);
}

WorldRenderer::~WorldRenderer() {
    for (auto& it : terrainMeshes1){
        delete it.second;
    }
    terrainMeshes1.clear();
}

void WorldRenderer::renderScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //DepthMap gen
    depthBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    renderTerrain(); //TODO do a bare bones vs shader render, fs shouldn't do anything
    depthBuffer.unbind();

    renderBuffer.bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Global::sun->render();
    renderTerrain();
    Global::skybox->render();

    renderBuffer.unbind();

    //renderFog(); //Skybox and breaks bloom?
    applyBloom(); //Use better blurring or predefined texture map for sun
    applyColorCorrection();
    applyToneMapping();
    applyGammaCorrection();

    //Util::renderTexture(depthBuffer.getTextureId());
    Util::renderTexture(renderBuffer.getTextureId());
}

void WorldRenderer::renderTerrain() {
    auto map = getTerrainMeshesReadMap();
    for (auto& it : map){
        Block& block = Blocks::getById(it.first);
        Mesh* mesh = it.second;
        renderBlockMesh(block, mesh);
    }
}


std::unordered_map<uint16_t, Mesh *>& WorldRenderer::getTerrainMeshesWriteMap() {
    std::scoped_lock sl(swapMutex);
    return *terrainMeshesWriteMap;
}

std::unordered_map<uint16_t, Mesh *>& WorldRenderer::getTerrainMeshesReadMap() {
    std::scoped_lock sl(swapMutex);
    return *terrainMeshesReadMap;
}

void WorldRenderer::renderBlockMesh(Block &block, Mesh *mesh) {
    Shader& shader = block.getMaterial().shader;
    block.getMaterial().texture.bind();
    shader.use();
    mesh->bindVertexArray();

    shader.setMat4("projection", Global::currentFrame.projection);
    shader.setMat4("view", Global::currentFrame.view);
    shader.setMat4("model", Global::currentFrame.model);
    shader.setFloat("uTime", (float)glfwGetTime()); //TODO this only needs to happen for grass

    shader.setVec3("lightColor", Global::sun->getColor());
    shader.setVec3("lightDir", Global::sun->getLightDir());
    shader.setVec3("viewPos", Global::camera.pos);

    shader.setFloat("ambientStrength", block.getMaterial().ambientStrength);
    shader.setFloat("specularStrength", block.getMaterial().specularStrength);
    shader.setInt("shininess", block.getMaterial().shininess);

    glDrawArrays(GL_TRIANGLES, 0, (int)mesh->getVerticesCount()); //@Danger
}

void WorldRenderer::applyBloom() {

    //Separate dark and bright parts of the scene
    Shader* bloomContrastShader = Global::shaderManager.getAsset(Shaders::BLOOM_CONTRAST);
    bloomContrastShader->use();
    renderBuffer.bindTexture(0);
    bloomContrastShader->setInt("renderTexture", 0);
    bloomContrastShader->setFloat("threshold", GraphicsConfiguration::bloomThreshold);

    bloomBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    Util::renderQuad();
    bloomBuffer.unbind();

    //Generate Blurred images
    int texWidth = Configuration::windowWidth, texHeight = Configuration::windowHeight;
    int scaledTexWidth =  texWidth/2, scaledTexHeight = texHeight/2;
    int i;
    for (i=0; i<8; i++){
        glBlitNamedFramebuffer(bloomBuffer.getID(), mipLevels[i].getID(), 0,0, texWidth, texHeight, 0,0, scaledTexWidth, scaledTexHeight,  GL_COLOR_BUFFER_BIT, GL_LINEAR);
        glBlitNamedFramebuffer(mipLevels[i].getID(), scaledImages[i].getID(),  0,0, scaledTexWidth, scaledTexHeight, 0,0, texWidth, texHeight,  GL_COLOR_BUFFER_BIT, GL_LINEAR);

        if (scaledTexHeight < 20)
            break;

        scaledTexWidth/=2;
        scaledTexHeight/=2;
    }

    //Apply Bloom
    Shader* bloomShader = Global::shaderManager.getAsset(Shaders::BLOOM);
    bloomShader->use();
    renderBuffer.bindTexture(0);
    bloomShader->setInt("renderTexture", 0);

    scaledImages[0].bindTexture(1);
    bloomShader->setInt("mipLevel0", 1);
    scaledImages[1].bindTexture(2);
    bloomShader->setInt("mipLevel1", 2);
    scaledImages[2].bindTexture(3);
    bloomShader->setInt("mipLevel2", 3);
    /*scaledImages[3].bindTexture(4);
    bloomShader->setInt("mipLevel3", 4);
    scaledImages[4].bindTexture(5);
    bloomShader->setInt("mipLevel4", 5);
    scaledImages[5].bindTexture(6);
    bloomShader->setInt("mipLevel5", 6);
    scaledImages[6].bindTexture(7);
    bloomShader->setInt("mipLevel6", 7);
    scaledImages[7].bindTexture(8);
    bloomShader->setInt("mipLevel7", 8);*/

    bloomShader->setInt("bloomDecay", GraphicsConfiguration::bloomDecay);

    renderBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    Util::renderQuad();
    renderBuffer.unbind();
}

void WorldRenderer::applyToneMapping() {

    Shader* luminanceTextureShader = Global::shaderManager.getAsset(Shaders::LUMINANCE_TEXTURE);
    luminanceTextureShader->use();
    renderBuffer.bindTexture(0);
    luminanceTextureShader->setInt("renderTexture", 0);

    toneMapperBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    Util::renderQuad();
    toneMapperBuffer.unbind();


    Shader* trMapper = Global::shaderManager.getAsset(Shaders::TONE_MAPPER_NACES);
    trMapper->use();
    renderBuffer.bindTexture(0);
    //toneMapperBuffer.bindTexture(1);

    trMapper->setInt("renderTexture", 0);
    /*trMapper->setInt("luminanceTexture", 1);
    trMapper->setFloat("lumMax", 100.0f);
    trMapper->setFloat("cMax", 10.0f);*/

    renderBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    Util::renderQuad();
    renderBuffer.unbind();
}

void WorldRenderer::applyColorCorrection() {
    Shader* colorShader = Global::shaderManager.getAsset(Shaders::COLOR_CORRECTION);
    colorShader->use();

    renderBuffer.bindTexture(0);
    colorShader->setInt("renderTexture", 0);
    colorShader->setFloat("contrast", GraphicsConfiguration::contrast);
    colorShader->setFloat("brightness", GraphicsConfiguration::brightness);
    colorShader->setFloat("saturation", GraphicsConfiguration::saturation);

    renderBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    Util::renderQuad();
    renderBuffer.unbind();
}

void WorldRenderer::applyGammaCorrection() {
    Shader* gammaShader = Global::shaderManager.getAsset(Shaders::GAMMA_CORRECTION);
    gammaShader->use();

    renderBuffer.bindTexture(0);
    gammaShader->setInt("renderTexture", 0);
    gammaShader->setFloat("gamma", GraphicsConfiguration::gamma);

    renderBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    Util::renderQuad();
    renderBuffer.unbind();
}

void WorldRenderer::renderFog() {
    Shader* fogShader = Global::shaderManager.getAsset(Shaders::FOG);
    fogShader->use();

    depthBuffer.bindTexture(0);
    renderBuffer.bindTexture(1);
    Global::textureManager.getAsset(Textures::FOG)->bind(2);

    fogShader->setInt("depthTexture", 0);
    fogShader->setInt("renderTexture", 1);
    fogShader->setInt("fogTexture", 2);
    fogShader->setFloat("fogStrength", GraphicsConfiguration::fogStrength);
    fogShader->setInt("fogDistance", GraphicsConfiguration::fogDistance);

    renderBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    Util::renderQuad();
    renderBuffer.unbind();
}

void WorldRenderer::renderShadows() {
    float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
                                      glm::vec3( 0.0f, 0.0f,  0.0f),
                                      glm::vec3( 0.0f, 1.0f,  0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    //shadow render
    glViewport(0, 0, GraphicsConfiguration::shadowWidth, GraphicsConfiguration::shadowWidth);
    depthBuffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT);

    shadowShader->use();
    shadowShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    shadowShader->setMat4("model", glm::mat4(1.0f));

    //renderScene();
    depthBuffer.unbind();
}

void WorldRenderer::swapMaps() {
    swapMutex.lock();
    if (terrainMeshesWriteMap == &terrainMeshes1){
        terrainMeshesWriteMap = &terrainMeshes2;
        terrainMeshesReadMap =  &terrainMeshes1;
    }else{
        terrainMeshesWriteMap = &terrainMeshes1;
        terrainMeshesReadMap =  &terrainMeshes2;
    }
    swapMutex.unlock();
}
