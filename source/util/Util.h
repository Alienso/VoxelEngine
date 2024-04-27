//
// Created by Alienson on 24.4.2024..
//

#ifndef VOXEL_UTIL_H
#define VOXEL_UTIL_H

#include <memory>
#include "glm/glm.hpp"
#include "render/Shader.h"

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


#endif //VOXEL_UTIL_H
