#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding=0) uniform sampler2D texture1;

void main(){
    float val = pow(texture(texture1, TexCoords).r, 4);
    FragColor = vec4(val, val, val, 1.0);
}