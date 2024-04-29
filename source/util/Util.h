//
// Created by Alienson on 24.4.2024..
//

#ifndef VOXEL_UTIL_H
#define VOXEL_UTIL_H

#include "glm/glm.hpp"
#include "render/Shader.h"

#include <memory>
#include <chrono>
#include <iostream>

struct GlmVec3Functions {
    size_t operator()(const glm::ivec3& k) const {
        return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z);
    }

    bool operator()(const glm::ivec3& a, const glm::ivec3& b) const {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};

class Util{
public:
    static void renderTexture(unsigned int texture);
    static void renderQuad();

private:
    static unsigned int quadVAO;
    static unsigned int quadVBO;
};


class Timer{
public:
    Timer(const char* name) : name(name){
        startTimePoint = std::chrono::steady_clock::now();
    }
    ~Timer(){
        if (!stopped)
            stop();
    }

    void stop(){
        auto endTimePoint = std::chrono::steady_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(startTimePoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();

        std::cout << name << " took " <<end - start << "ms\n";

        stopped = true;
    }

private:
    const char* name;
    std::chrono::time_point<std::chrono::steady_clock> startTimePoint;
    bool stopped;
};


#endif //VOXEL_UTIL_H
