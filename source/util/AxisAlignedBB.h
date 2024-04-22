//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_AXISALIGNEDBB_H
#define INC_3DTEST_AXISALIGNEDBB_H

#include "glm/glm.hpp"

class AxisAlignedBB {

public:
    glm::vec3 minBounds{};
    glm::vec3 maxBounds{};

    AxisAlignedBB(){
        maxBounds = minBounds = glm::vec3(0,0,0);
    }
};


#endif //INC_3DTEST_AXISALIGNEDBB_H
