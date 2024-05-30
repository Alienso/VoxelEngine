//
// Created by Alienson on 21.4.2024..
//

#include "Block.h"
#include "Global.h"
#include "Blocks.h"
#include "CubeVerticesTypes.h"

#include <string>
#include <GLFW/glfw3.h>

using namespace std;

Block::Block(const char *name, int id, BlockTextureRenderTypeEnum renderType, bool transparent, bool neverRenderSides, Shader* shader) : id(id), name(name), transparent(transparent), neverRenderSides(neverRenderSides) {
    string path = "textures/block/" + string(name) + ".png";
    Texture& texture = Global::textureManager.createAsset(name, path.data(), GL_RGBA);
    material = &(Global::materialManager.createAsset(name, *shader, texture));

    regularBlock = true;
    blockCounter++;

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
        case BLOCK_TEXTURE_X:
            verticesPtr = &CubeVerticesTypes::cubeVerticesX;
            regularBlock = false;
            material->ambientStrength = 0.8f;
            break;
    }
}
