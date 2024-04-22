//
// Created by Alienson on 16.4.2024..
//

#include "Asset.h"
#include "AppName.h"
#include "core/render/Texture.h"
#include "core/render/Material.h"
#include "Global.h"

void AppName::initAssets(){

    Shader& shader = Global::shaderManager.createAsset(Shaders::BASE, "3D.vs", "3D.fs");
    Shader& lightSourceShader = Global::shaderManager.createAsset(Shaders::LIGHT_SOURCE, "lightSource.vs", "lightSource.fs");

    Texture& texture = Global::textureManager.createAsset(Textures::MOUNTAINS,"Background.jpg", GL_RGB);

    Material& base = Global::materialManager.createAsset(Materials::BASE, lightSourceShader, texture);
    Material& light = Global::materialManager.createAsset(Materials::LIGHT, lightSourceShader, texture);

}