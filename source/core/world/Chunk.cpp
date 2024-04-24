//
// Created by Alienson on 21.4.2024..
//

#include "Chunk.h"

glm::vec3 Chunk::posFromIndex(int i) { //TODO optimize
    int y = i / 256;
    int plane = i - y*256;
    int x = plane / 16;
    int z = plane - x*16;
    return {x,y,z};
}
