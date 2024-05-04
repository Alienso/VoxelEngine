//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_BLOCK_H
#define VOXEL_BLOCK_H


#include "render/Material.h"
#include "render/WorldRenderer.h"
#include "Global.h"

enum BlockTextureRenderTypeEnum{
    BLOCK_TEXTURE_SINGLE, // All sides are same
    BLOCK_TEXTURE_TOP_BOTTOM, //Log
    BLOCK_TEXTURE_TOP, // Grass
    BLOCK_TEXTURE_FRONT, // Furnace
    BLOCK_TEXTURE_MULTI, //All sides are different
    BLOCK_TEXTURE_X // Grass
};

class Block {
public:
    Block(const char* name, int id, BlockTextureRenderTypeEnum renderType, bool transparent = false, Shader* shader = Global::shaderManager.getAsset(Shaders::BASE));

    [[nodiscard]] constexpr uint16_t getId() const{
        return id;
    }
    [[nodiscard]] std::vector<float>* getVerticesPtr() const{
        return verticesPtr;
    }
    [[nodiscard]] const Material& getMaterial(){
        return *material;
    }
    [[nodiscard]] bool isTransparent() const{
        return transparent;
    }
    [[nodiscard]] bool isRegularBlock() const{
        return regularBlock;
    }

    friend WorldRenderer;

private:
    static inline int blockCounter = 0;
    const int id;
    std::string name;

    bool transparent;
    bool regularBlock;

    Material* material;
    std::vector<float>* verticesPtr;
};


#endif //VOXEL_BLOCK_H
