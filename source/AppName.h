//
// Created by Alienson on 16.4.2024..
//

#ifndef INC_3DTEST_APPNAME_H
#define INC_3DTEST_APPNAME_H

#include <thread>
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

    bool shouldContinue = true;
    World* world = nullptr;

    std::thread logicThread;
    std::thread terrainUpdateThread;

    double lastLogicTime;
    double lastMainTime;
};


#endif //INC_3DTEST_APPNAME_H
