//
// Created by Alienson on 3.5.2024..
//

#ifndef VOXEL_BIOME_H
#define VOXEL_BIOME_H


#include <string>
#include "world/Block.h"
#include "entity/Entity.h"
#include "world/gen/PlantGenerator.h"
#include "world/gen/TreeGenerator.h"
#include "BiomeDecorator.h"

#include "Biomes.h"
#include "world/Chunk.h"

class Biome {
public:
    Biome() = default;

    void decorateChunk(Chunk* chunk);

    friend Biomes;

    std::string name;
    int baseHeight;
    int heightVariation;
    float rainfall;
    float temperature;

    Block* topBlock;
    Block* fillerBlock;
    int topBlockHeight;

    std::vector<Entity*> spawnableMonsterList;
    std::vector<Entity*> spawnableCreatureList;

private:
    PlantGenerator plantGenerator;
    TreeGenerator treeGenerator;
    BiomeDecorator decorator;

};


#endif //VOXEL_BIOME_H
