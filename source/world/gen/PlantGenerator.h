//
// Created by Alienson on 3.5.2024..
//

#ifndef VOXEL_PLANTGENERATOR_H
#define VOXEL_PLANTGENERATOR_H


#include "world/Chunk.h"
#include <cstdlib>

class PlantGenerator {
public:
    PlantGenerator();
    void decorate(Chunk* chunk);
private:
    PerlinNoise perlinNoise{(unsigned int)(rand() * 100000) % 100000};
    float scale;
    float threshold;
};


#endif //VOXEL_PLANTGENERATOR_H
