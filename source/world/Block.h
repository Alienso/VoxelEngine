//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_BLOCK_H
#define VOXEL_BLOCK_H


#include "render/Material.h"
#include "render/WorldRenderer.h"

class Block {
public:
    explicit Block(const char* name, int id = blockCounter);

    [[nodiscard]] constexpr uint16_t getId() const{
        return id;
    }
    /*const Material& getMaterial(){
        return *material;
    }*/

    friend WorldRenderer;

private:
    static inline int blockCounter = 0;
    const int id;
    std::string name;
    //Material* material;
    std::vector<Texture*> blockTextures;
};


#endif //VOXEL_BLOCK_H
