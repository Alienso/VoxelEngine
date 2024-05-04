//
// Created by Alienson on 3.5.2024..
//

#include "Biomes.h"
#include "Biome.h"
#include "world/Blocks.h"

Biome* generatePlains(){
    auto* biome = new Biome();

    biome->name = "Plains";
    biome->baseHeight = 0;
    biome->heightVariation = 10;
    biome->rainfall = 1.0f;
    biome->temperature = 20.0f;

    biome->topBlock = Blocks::GRASS_BLOCK;
    biome->fillerBlock = Blocks::STONE;
    biome->topBlockHeight = 5;

    biome->spawnableMonsterList = {};
    biome->spawnableCreatureList = {};

    return biome;
}

Biome* generateDesert(){
    auto* biome = new Biome();

    biome->name = "Desert";
    biome->baseHeight = 5;
    biome->heightVariation = 5;
    biome->rainfall = 0.0f;
    biome->temperature = 40.0f;

    biome->topBlock = Blocks::SAND;
    biome->fillerBlock = Blocks::STONE;
    biome->topBlockHeight = 5;

    biome->spawnableMonsterList = {};
    biome->spawnableCreatureList = {};

    return biome;
}

Biome* Biomes::PLAINS = generatePlains();
Biome* Biomes::DESERT = generateDesert();

Biomes::~Biomes() {
    delete PLAINS;
    delete DESERT;
}
