#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding=0) uniform sampler2D renderTexture;

uniform float threshold;

void main(){
    vec3 value = texture(renderTexture, TexCoords).rgb;
    if ((value.r + value.g + value.b) / 3 > threshold)
        FragColor = vec4(value, 1.0);
    else FragColor = vec4(0,0,0,1);
}