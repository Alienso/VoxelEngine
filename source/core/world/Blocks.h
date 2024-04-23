//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_BLOCKS_H
#define VOXEL_BLOCKS_H

#include "Block.h"
#include <vector>

class Blocks{
public:
    static inline Block* AIR = nullptr;
    static inline Block* GRASS = nullptr;
    static inline Block* DIRT = nullptr;

    static void init();

    static Block &getById(const uint16_t id) {
        return *blocks[id];
    }

private:
    static inline std::vector<Block*> blocks{256};

    friend Block;
};

#endif //VOXEL_BLOCKS_H
