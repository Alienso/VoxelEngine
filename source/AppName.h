//
// Created by Alienson on 16.4.2024..
//

#ifndef INC_3DTEST_APPNAME_H
#define INC_3DTEST_APPNAME_H

#include "world/World.h"

class AppName {
public:
    AppName() = default;
    void run();

private:
    void init();
    void mainLoop();
    void cleanup();

    void initGlfw();
    void initImGui();
    void initAssets();

    void renderImGui();

    World* world = nullptr;
};


#endif //INC_3DTEST_APPNAME_H
