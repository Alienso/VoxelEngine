//
// Created by Alienson on 28.5.2023..
//

#include "Material.h"

Material::Material(Shader &shader, Texture &texture) : shader(shader), texture(texture) {
    ambientStrength = 0.35;
    specularStrength = 0.1;
    shininess = 2;
}

Material &Material::withAmbientStrength(float a) {
    ambientStrength = a;
    return *this;
}

Material &Material::withSpecularStrength(float s) {
    specularStrength = s;
    return *this;
}

Material &Material::withShininess(int s) {
    shininess = s;
    return *this;
}
