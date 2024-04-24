//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_MATERIAL_H
#define INC_3DTEST_MATERIAL_H


#include "Shader.h"
#include "Texture.h"

class Material {
public:
    Material(Shader& shader, Texture& texture);

    Material& withAmbientStrength(float a);
    Material& withSpecularStrength(float s);
    Material& withShininess(int s);

    Shader& shader;
    Texture& texture;

    float ambientStrength;
    float specularStrength;
    int shininess;

private:

};


#endif //INC_3DTEST_MATERIAL_H
