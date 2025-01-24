#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

uniform int bloomDecay;

layout(binding=0) uniform sampler2D renderTexture;
layout(binding=1) uniform sampler2D mipLevel0;
layout(binding=2) uniform sampler2D mipLevel1;
layout(binding=3) uniform sampler2D mipLevel2;
layout(binding=4) uniform sampler2D mipLevel3;
layout(binding=5) uniform sampler2D mipLevel4;
layout(binding=6) uniform sampler2D mipLevel5;
layout(binding=7) uniform sampler2D mipLevel6;
layout(binding=8) uniform sampler2D mipLevel7;


void main(){
    vec4 bloomColor =  texture(mipLevel0, TexCoords) / bloomDecay
                     + texture(mipLevel1, TexCoords) /  (bloomDecay * 2)
                     + texture(mipLevel2, TexCoords) /  (bloomDecay * 4);
                     //+ texture(mipLevel3, TexCoords) /  (bloomDecay * 8)
                     //+ texture(mipLevel4, TexCoords) /  (bloomDecay * 16)
                     //+ texture(mipLevel5, TexCoords) /  (bloomDecay * 32);
                     //+ texture(mipLevel6, TexCoords) /  (bloomDecay * 32)
                     //+ texture(mipLevel7, TexCoords) /  (bloomDecay * 32);
    if (bloomColor.a < 0.5)
        bloomColor.a = 0;
    FragColor = texture(renderTexture, TexCoords) + bloomColor;

}