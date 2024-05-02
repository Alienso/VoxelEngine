//
// Created by Alienson on 16.4.2024..
//

#ifndef INC_3DTEST_ASSET_H
#define INC_3DTEST_ASSET_H

class Textures{
public:
    static inline const char* MOUNTAINS = "mountains";
    static inline const char* SKYBOX = "skybox";
};

class Shaders{
public:
    static inline const char* BASE = "base";
    static inline const char* LIGHT_SOURCE = "lightSource";
    static inline const char* SKYBOX = "skybox";
    static inline const char* SHADOW = "shadow";
    static inline const char* TEXTURE = "texture";
    static inline const char * TEXTURE_MONO = "textureMono";
};

class Materials{
public:
    static inline const char* BASE = "base";
    static inline const char* LIGHT = "light";
    static inline const char* SKYBOX = "skybox";
};

#endif //INC_3DTEST_ASSET_H
