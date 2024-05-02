//
// Created by Alienson on 21.4.2024..
//

#include "Block.h"
#include "Global.h"
#include "Blocks.h"
#include "CubeVerticesTypes.h"

#include <string>

using namespace std;

Block::Block(const char *name, int id, BlockTextureRenderTypeEnum renderType ) : id(id), name(name) {
    blockCounter++;
    string path = "textures/block/" + string(name) + ".png";
    Texture& texture = Global::textureManager.createAsset(name, path.data(), GL_RGBA);

    Shader* shader = Global::shaderManager.getAsset(Shaders::BASE);
    material = &(Global::materialManager.createAsset(name, *shader, texture));

    if ((int)Blocks::blocks.size() <= id){
        Blocks::blocks.resize(id + 1);
    }
    Blocks::blocks[id] = this;

    switch (renderType) {
        case BLOCK_TEXTURE_SINGLE:
            verticesPtr = &CubeVerticesTypes::cubeVerticesSingle;
            break;
        case BLOCK_TEXTURE_TOP:
            verticesPtr = &CubeVerticesTypes::cubeVerticesTop;
            break;
        case BLOCK_TEXTURE_FRONT:
            verticesPtr = &CubeVerticesTypes::cubeVerticesFront;
            break;
        case BLOCK_TEXTURE_TOP_BOTTOM:
            verticesPtr = &CubeVerticesTypes::cubeVerticesTopBottom;
            break;
        case BLOCK_TEXTURE_MULTI:
            verticesPtr = &CubeVerticesTypes::cubeVerticesMulti;
            break;
    }
}
