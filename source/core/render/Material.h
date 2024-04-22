//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_MATERIAL_H
#define INC_3DTEST_MATERIAL_H


#include "Shader.h"
#include "Texture.h"

class Material {
public:
    Material(Shader& shader, Texture& texture) : shader(shader), texture(texture) {}
    Shader& shader;
    Texture& texture;

private:
    //TODO
    float specularStrength;
    float shininess;
};


#endif //INC_3DTEST_MATERIAL_H
