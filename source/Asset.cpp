//
// Created by Alienson on 16.4.2024..
//

#include "Asset.h"
#include "AppName.h"
#include "render/Texture.h"
#include "render/Material.h"
#include "Global.h"

void AppName::initAssets(){

    [[maybe_unused]] Shader& basicShader = Global::shaderManager.createAsset(Shaders::BASE, "3D.vs", "3D.fs");
    Shader& lightSourceShader = Global::shaderManager.createAsset(Shaders::LIGHT_SOURCE, "lightSource.vs", "lightSource.fs");
    Shader& skyboxShader = Global::shaderManager.createAsset(Shaders::SKYBOX, "skybox.vs", "skybox.fs");
    [[maybe_unused]] Shader& shadowShader = Global::shaderManager.createAsset(Shaders::SHADOW, "directLightShadow.vs", "directLightShadow.fs");
    [[maybe_unused]] Shader& textureShader = Global::shaderManager.createAsset(Shaders::TEXTURE, "texture.vs", "texture.fs");

    Texture& baseTexture = Global::textureManager.createAsset(Textures::MOUNTAINS, "Background.jpg", GL_RGB);
    Texture* skyboxTexture = Texture::generateCubeMap(Skybox::resourcePath, GL_RGB);
    Global::textureManager.registerAsset(Textures::SKYBOX, skyboxTexture);

    [[maybe_unused]] Material& base = Global::materialManager.createAsset(Materials::BASE, lightSourceShader, baseTexture);
    [[maybe_unused]] Material& light = Global::materialManager.createAsset(Materials::LIGHT, lightSourceShader, baseTexture);
    [[maybe_unused]] Material& skybox = Global::materialManager.createAsset(Materials::SKYBOX, skyboxShader, *skyboxTexture);

}