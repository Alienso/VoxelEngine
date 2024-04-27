//
// Created by Alienson on 26.4.2024..
//

#ifndef VOXEL_ENUMFACING_H
#define VOXEL_ENUMFACING_H

#include "glm/vec3.hpp"

class EnumFacing{

public:
    glm::ivec3 dirVec;

private:
    EnumFacing(int x,int y, int z);

    const static EnumFacing* WEST;
    const static EnumFacing* EAST;
    const static EnumFacing* NORTH;
    const static EnumFacing* SOUTH;
    const static EnumFacing* UP;
    const static EnumFacing* DOWN;
};

#endif //VOXEL_ENUMFACING_H
