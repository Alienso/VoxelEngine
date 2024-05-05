#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding=0) uniform sampler2D renderTexture;

uniform float gamma;

void main(){
    vec3 color = texture(renderTexture, TexCoords).rgb;
    FragColor = vec4(vec3(pow(color.r, gamma), pow(color.g, gamma), pow(color.b, gamma)), 1.0);
}