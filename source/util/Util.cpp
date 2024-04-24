//
// Created by Alienson on 23.4.2024..
//

#include <memory>
#include "glm/glm.hpp"

struct GlmVec3Functions {
    size_t operator()(const glm::u32vec3& k) const {
        return std::hash<uint32_t>()(k.x) ^ std::hash<uint32_t>()(k.y) ^ std::hash<uint32_t>()(k.z);
    }

    bool operator()(const glm::u32vec3& a, const glm::u32vec3& b) const {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};