//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_BLOCK_H
#define VOXEL_BLOCK_H


#include "render/Material.h"
#include "render/WorldRenderer.h"

enum BlockTextureRenderTypeEnum{
    BLOCK_TEXTURE_SINGLE, // All sides are same
    BLOCK_TEXTURE_TOP_BOTTOM, //Log
    BLOCK_TEXTURE_TOP, // Grass
    BLOCK_TEXTURE_FRONT, //Furnace
    BLOCK_TEXTURE_MULTI //All sides are different
};

class Block {
public:
    Block(const char* name, int id, BlockTextureRenderTypeEnum renderType );

    [[nodiscard]] constexpr uint16_t getId() const{
        return id;
    }
    [[nodiscard]] std::vector<float>* getVerticesPtr() const{
        return verticesPtr;
    }
    const Material& getMaterial(){
        return *material;
    }

    friend WorldRenderer;

private:
    static inline int blockCounter = 0;
    const int id;
    std::string name;
    Material* material;
    std::vector<float>* verticesPtr;
};


#endif //VOXEL_BLOCK_H
