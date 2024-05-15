//
// Created by Alienson on 16.4.2024..
//

#include "Asset.h"
#include "AppName.h"
#include "render/Texture.h"
#include "render/Material.h"
#include "Global.h"

#include <GLFW/glfw3.h>

void AppName::initAssets(){

    Shader& lightSourceShader = Global::shaderManager.createAsset(Shaders::LIGHT_SOURCE, "sun.vs", "sun.fs");
    Shader& skyboxShader = Global::shaderManager.createAsset(Shaders::SKYBOX, "skybox.vs", "skybox.fs");
    [[maybe_unused]] Shader& basicShader = Global::shaderManager.createAsset(Shaders::BASE, "3D.vs", "3D.fs");
    [[maybe_unused]] Shader& shadowShader = Global::shaderManager.createAsset(Shaders::SHADOW, "directLightShadow.vs", "directLightShadow.fs");
    [[maybe_unused]] Shader& textureShader = Global::shaderManager.createAsset(Shaders::TEXTURE, "texture.vs", "texture.fs");
    [[maybe_unused]] Shader& textureMonoShader = Global::shaderManager.createAsset(Shaders::TEXTURE_MONO, "texture.vs", "texture_mono.fs");
    [[maybe_unused]] Shader& grassShader = Global::shaderManager.createAsset(Shaders::GRASS, "grass.vs", "3D.fs");
    [[maybe_unused]] Shader& leavesShader = Global::shaderManager.createAsset(Shaders::LEAVES, "leaves.vs", "3D.fs");
    [[maybe_unused]] Shader& fogShader = Global::shaderManager.createAsset(Shaders::FOG, "texture.vs", "fog.fs");
    [[maybe_unused]] Shader& bloomShader = Global::shaderManager.createAsset(Shaders::BLOOM, "texture.vs", "bloom.fs");
    [[maybe_unused]] Shader& bloomContrastShader = Global::shaderManager.createAsset(Shaders::BLOOM_CONTRAST, "texture.vs", "bloom_contrast.fs");
    [[maybe_unused]] Shader& toneMapperTRShader = Global::shaderManager.createAsset(Shaders::TONE_MAPPER_TR, "texture.vs", "tone_mapper_tumblin_rushmier.fs");
    [[maybe_unused]] Shader& toneMapperNAces = Global::shaderManager.createAsset(Shaders::TONE_MAPPER_NACES, "texture.vs", "tone_mapper_narkowiez_aces.fs");
    [[maybe_unused]] Shader& luminanceTextureShader = Global::shaderManager.createAsset(Shaders::LUMINANCE_TEXTURE, "texture.vs", "luminance_texture.fs");
    [[maybe_unused]] Shader& colorCorrectionShader = Global::shaderManager.createAsset(Shaders::COLOR_CORRECTION, "texture.vs", "color_correction.fs");
    [[maybe_unused]] Shader& gammaCorrectionShader = Global::shaderManager.createAsset(Shaders::GAMMA_CORRECTION, "texture.vs", "gamma_correction.fs");
    [[maybe_unused]] Shader& waterShader = Global::shaderManager.createAsset(Shaders::WATER, "water.vs", "water.fs");

    Texture& baseTexture = Global::textureManager.createAsset(Textures::BLANK, "blank.png", GL_RGB);
    Texture* skyboxTexture = Texture::generateCubeMap(Skybox::resourcePath, GL_RGB);
    Global::textureManager.registerAsset(Textures::SKYBOX, skyboxTexture);
    [[maybe_unused]] Texture& fogTexture = Global::textureManager.createAsset(Textures::FOG, "fog.png", GL_RGBA);

    [[maybe_unused]] Material& base = Global::materialManager.createAsset(Materials::BASE, lightSourceShader, baseTexture);
    [[maybe_unused]] Material& light = Global::materialManager.createAsset(Materials::LIGHT, lightSourceShader, baseTexture);
    [[maybe_unused]] Material& skybox = Global::materialManager.createAsset(Materials::SKYBOX, skyboxShader, *skyboxTexture);

}