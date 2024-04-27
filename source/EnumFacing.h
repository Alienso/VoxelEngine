//
// Created by Alienson on 26.4.2024..
//

#ifndef VOXEL_ENUMFACING_H
#define VOXEL_ENUMFACING_H

#include "glm/vec3.hpp"
#include <vector>

class EnumFacing{

public:
    glm::ivec3 dirVec;
    const size_t id;

    const static EnumFacing* WEST;
    const static EnumFacing* EAST;
    const static EnumFacing* NORTH;
    const static EnumFacing* SOUTH;
    const static EnumFacing* UP;
    const static EnumFacing* DOWN;
    static std::vector<const EnumFacing*> sides;

private:
    EnumFacing(int x,int y, int z, int id);
};

#endif //VOXEL_ENUMFACING_H
