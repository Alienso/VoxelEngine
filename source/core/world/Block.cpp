//
// Created by Alienson on 21.4.2024..
//

#include "Block.h"
#include "./../source/Global.h"
#include "Blocks.h"

#include <string>

using namespace std;

Block::Block(const char *name, int id) : name(name), id(id) {
    blockCounter++;
    string path = "textures/block/" + string(name) + ".png";
    Texture& texture = Global::textureManager.createAsset(name, path.data(), GL_RGBA);

    Shader* shader = Global::shaderManager.getAsset(Shaders::BASE);
    material = &(Global::materialManager.createAsset(name, *shader, texture));

    if ((int)Blocks::blocks.size() <= id){
        Blocks::blocks.resize(id + 1);
    }
    Blocks::blocks[id] = this;
}
