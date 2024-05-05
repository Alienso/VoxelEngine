#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding=0) uniform sampler2D renderTexture;

void main(){
    vec3 color = texture(renderTexture, TexCoords).rgb;
    float luminance = 0.2126*color.r + 0.7152*color.g + 0.0722*color.b;
    FragColor = vec4(vec3(luminance, luminance, luminance), 1);
}