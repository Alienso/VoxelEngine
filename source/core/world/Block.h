//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_BLOCK_H
#define VOXEL_BLOCK_H


#include "../render/Material.h"

class Block {
public:
    explicit Block(const char* name, int id = blockCounter);

    const Material& getMaterial(){
        return *material;
    }
private:
    static inline int blockCounter = 0;
    std::string name;
    int id;
    Material* material;
};


#endif //VOXEL_BLOCK_H
