//
// Created by Alienson on 27.4.2024..
//

#include "EnumFacing.h"

EnumFacing::EnumFacing(int x, int y, int z) : dirVec({x, y, z}) {}

const EnumFacing* EnumFacing::WEST = new EnumFacing(-1,0,0);
const EnumFacing* EnumFacing::EAST = new EnumFacing(1,0,0);
const EnumFacing* EnumFacing::NORTH = new EnumFacing(0,0,-1);
const EnumFacing* EnumFacing::SOUTH = new EnumFacing(0,0,1);
const EnumFacing* EnumFacing::UP = new EnumFacing(0,1,0);
const EnumFacing* EnumFacing::DOWN = new EnumFacing(0,-1,0);


