//
// Created by Alienson on 22.4.2024..
//
#include "Blocks.h"

void Blocks::init() {
    AIR = new Block("air",0, BLOCK_TEXTURE_SINGLE);
    GRASS = new Block("grass",1, BLOCK_TEXTURE_MULTI);
    DIRT = new Block("dirt",2, BLOCK_TEXTURE_SINGLE);
}

