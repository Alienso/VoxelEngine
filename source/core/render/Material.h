//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_MATERIAL_H
#define INC_3DTEST_MATERIAL_H


#include "Shader.h"
#include "Texture.h"

class Material {
public:
    Material(Shader& shader, Texture& texture) : shader(shader), texture(texture) {
        //TODO
        ambientStrength = 0.1;
        specularStrength = 0.5;
        shininess = 2;
    }
    Shader& shader;
    Texture& texture;

    //TODO
    float ambientStrength;
    float specularStrength;
    int shininess;

private:

};


#endif //INC_3DTEST_MATERIAL_H
