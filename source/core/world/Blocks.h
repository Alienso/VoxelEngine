//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_BLOCKS_H
#define VOXEL_BLOCKS_H

#include "Block.h"

class Blocks{
public:
    static inline Block AIR{"air",0};
    static inline Block GRASS{"grass",1};
    static inline Block DIRT{"dirt",2};

    static Block &getById(const uint16_t id) {
        return *blocks[id];
    }

private:
    static inline std::vector<Block*> blocks{256};

    friend Block;
};

#endif //VOXEL_BLOCKS_H
