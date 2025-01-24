//
// Created by Alienson on 3.5.2024..
//

#ifndef VOXEL_BIOMEPROVIDER_H
#define VOXEL_BIOMEPROVIDER_H


#include "Biome.h"

class BiomeProvider {
public:
    [[nodiscard]] Biome* getBiomeAt(int x, int y, int z) const;
};


#endif //VOXEL_BIOMEPROVIDER_H
