#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding=0) uniform sampler2D renderTexture;

void main(){
    vec3 color = texture(renderTexture, TexCoords).rgb;
    vec3 Cout = vec3((color * (2.51*color + 0.03)) / (color * (2.43*color + 0.59) + 0.14));
    FragColor = vec4(Cout, 1.0);
}