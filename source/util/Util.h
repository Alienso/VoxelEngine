//
// Created by Alienson on 24.4.2024..
//

#ifndef VOXEL_UTIL_H
#define VOXEL_UTIL_H

#include "glm/glm.hpp"
#include "render/Shader.h"
#include "render/Mesh.h"

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

typedef std::unordered_map<glm::ivec3, std::unordered_map<uint16_t, Mesh*>, GlmVec3Functions, GlmVec3Functions> terrainMeshMap;

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
    Timer(const char* name);
    ~Timer();
    void stop();

private:
    const char* name;
    std::chrono::time_point<std::chrono::steady_clock> startTimePoint;
    bool stopped;
};


#endif //VOXEL_UTIL_H
