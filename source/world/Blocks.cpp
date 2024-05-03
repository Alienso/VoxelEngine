//
// Created by Alienson on 22.4.2024..
//
#include "Blocks.h"

void Blocks::init() {
    AIR = new Block("air",0, BLOCK_TEXTURE_SINGLE, true);
    STONE = new Block("stone",1, BLOCK_TEXTURE_SINGLE);
    GRASS = new Block("grass",2, BLOCK_TEXTURE_MULTI);
    DIRT = new Block("dirt",3, BLOCK_TEXTURE_SINGLE);
    COBBLESTONE =  new Block("cobblestone",4, BLOCK_TEXTURE_SINGLE);
    OAK_WOOD_PLANK =  new Block("planks_oak",5, BLOCK_TEXTURE_SINGLE);
    OAK_SAPLING =  new Block("sapling_oak",6, BLOCK_TEXTURE_SINGLE);
    BEDROCK =  new Block("bedrock",7, BLOCK_TEXTURE_SINGLE);
    FLOWING_WATER =  new Block("water_flow",8, BLOCK_TEXTURE_SINGLE, true);
    STILL_WATER =  new Block("water_still",9, BLOCK_TEXTURE_SINGLE, true);
    FLOWING_LAVA =  new Block("lava_flow",10, BLOCK_TEXTURE_SINGLE);
    STILL_LAVA =  new Block("lava_still",11, BLOCK_TEXTURE_SINGLE);
    SAND =  new Block("sand",12, BLOCK_TEXTURE_SINGLE);
    GRAVEL =  new Block("gravel",13, BLOCK_TEXTURE_SINGLE);
    GOLD_ORE =  new Block("gold_ore",14, BLOCK_TEXTURE_SINGLE);
    IRON_ORE =  new Block("iron_ore",15, BLOCK_TEXTURE_SINGLE);
    COAL_ORE =  new Block("coal_ore",16, BLOCK_TEXTURE_SINGLE);
    OAK_WOOD =  new Block("log_oak",17, BLOCK_TEXTURE_TOP_BOTTOM);
    OAK_LEAVES =  new Block("leaves_oak",18, BLOCK_TEXTURE_SINGLE, true);
}

