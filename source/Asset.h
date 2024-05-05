//
// Created by Alienson on 16.4.2024..
//

#ifndef INC_3DTEST_ASSET_H
#define INC_3DTEST_ASSET_H

class Textures{
public:
    static inline const char* MOUNTAINS = "mountains";
    static inline const char* SKYBOX = "skybox";
    static inline const char* FOG = "fog";
};

class Shaders{
public:
    static inline const char* BASE = "base";
    static inline const char* LIGHT_SOURCE = "lightSource";
    static inline const char* SKYBOX = "skybox";
    static inline const char* SHADOW = "shadow";
    static inline const char* TEXTURE = "texture";
    static inline const char* TEXTURE_MONO = "textureMono";
    static inline const char* GRASS = "grass";
    static inline const char* FOG = "fog";
    static inline const char* BLOOM = "bloom";
    static inline const char* BLOOM_CONTRAST = "bloom_contrast";
    static inline const char* TONE_MAPPER_TR = "tone_mapper_tumblin_rushmier";
    static inline const char* LUMINANCE_TEXTURE = "luminance_texture";
    static inline const char* COLOR_CORRECTION = "color_correction";
    static inline const char* GAMMA_CORRECTION = "gamma_correction";
};

class Materials{
public:
    static inline const char* BASE = "base";
    static inline const char* LIGHT = "light";
    static inline const char* SKYBOX = "skybox";
};

#endif //INC_3DTEST_ASSET_H
