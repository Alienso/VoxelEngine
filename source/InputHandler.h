//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_INPUTHANDLER_H
#define VOXEL_INPUTHANDLER_H

#include "util/RayTrace.h"

class InputHandler {
public:
    static void processMouseInput();
    static void processKeyboardInput(float deltaTime);
    static RayTraceResult processMouseClick();
};


#endif //VOXEL_INPUTHANDLER_H
