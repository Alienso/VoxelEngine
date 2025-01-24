#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding=0) uniform sampler2D depthTexture;
layout(binding=1) uniform sampler2D renderTexture;
layout(binding=2) uniform sampler2D fogTexture;

uniform float fogStrength;
uniform int fogDistance;

void clampColor(inout vec3 color){
    if (color.r > 1)
        color.r = 1;
    else if (color.r < 0)
        color.r = 0;

    if (color.g > 1)
        color.g = 1;
    else if (color.g < 0)
        color.g = 0;

    if (color.b > 1)
        color.b = 1;
    else if (color.b < 0)
        color.b = 0;
}

void main(){
    float fogFactor = pow(texture(depthTexture, TexCoords).r, fogDistance) * fogStrength; //* (1 - TexCoords.y);
    vec3 fogColor = vec3(0.8,0.8,0.8); //texture(fogTexture, TexCoords).rgb;
    vec3 renderColor = texture(renderTexture, TexCoords).rgb;
    vec3 finalColor = mix(renderColor, fogColor, fogFactor);
    clampColor(finalColor);
    FragColor = vec4(finalColor,1.0);
    //FragColor = vec4( fogFactor * fogColor + (1 - fogFactor) * renderColor,  1.0);
}