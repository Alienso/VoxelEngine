#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding=0) uniform sampler2D depthTexture;
layout(binding=1) uniform sampler2D renderTexture;
layout(binding=2) uniform sampler2D fogTexture;

uniform float fogStrength;
uniform int fogDistance;

void main(){
    float fogFactor = pow(texture(depthTexture, TexCoords).r, fogDistance) * fogStrength; //* (1 - TexCoords.y);
    vec3 fogColor = vec3(0.8,0.8,0.8); //texture(fogTexture, TexCoords).rgb;
    vec3 renderColor = texture(renderTexture, TexCoords).rgb;
    FragColor = vec4( fogFactor * fogColor + (1 - fogFactor) * renderColor,  1.0);
}