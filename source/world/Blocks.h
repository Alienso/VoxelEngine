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
    static inline Block* STONE = nullptr;
    static inline Block* GRASS = nullptr;
    static inline Block* DIRT = nullptr;
    static inline Block* COBBLESTONE = nullptr;
    static inline Block* OAK_WOOD_PLANK = nullptr;
    static inline Block* OAK_SAPLING = nullptr;
    static inline Block* BEDROCK = nullptr;
    static inline Block* FLOWING_WATER = nullptr;
    static inline Block* STILL_WATER = nullptr;
    static inline Block* FLOWING_LAVA = nullptr;
    static inline Block* STILL_LAVA = nullptr;
    static inline Block* SAND = nullptr;
    static inline Block* GRAVEL = nullptr;
    static inline Block* GOLD_ORE = nullptr;
    static inline Block* IRON_ORE = nullptr;
    static inline Block* COAL_ORE = nullptr;
    static inline Block* OAK_WOOD = nullptr;
    static inline Block* OAK_LEAVES = nullptr;

    static void init();

    static Block &getById(const uint16_t id) {
        return *blocks[id];
    }

private:
    static inline std::vector<Block*> blocks{256};

    friend Block;
};

#endif //VOXEL_BLOCKS_H
