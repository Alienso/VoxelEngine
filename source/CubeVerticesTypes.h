//
// Created by Alienson on 2.5.2024..
//

#ifndef VOXEL_CUBEVERTICESTYPES_H
#define VOXEL_CUBEVERTICESTYPES_H

#include <vector>
#include <cstddef>

class CubeVerticesTypes{
public:
    static std::vector<size_t> cubeVerticesSideOffsets;
    static size_t cubeVerticesSideSize;
    static std::vector<float> cubeVerticesSingle;
    static std::vector<float> cubeVerticesTop;
    static std::vector<float> cubeVerticesFront;
    static std::vector<float> cubeVerticesTopBottom;
    static std::vector<float> cubeVerticesMulti;
};

#endif //VOXEL_CUBEVERTICESTYPES_H
