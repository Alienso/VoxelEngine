#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding=0) uniform sampler2D renderTexture;

uniform float contrast;
uniform float brightness;
uniform float saturation;
uniform float gamma;

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
    vec3 color = texture(renderTexture, TexCoords).rgb;
    color = contrast*(color- 0.5) + 0.5 + brightness;
    clampColor(color);
    vec3 grayscale = color * vec3(0.299, 0.587, 0.114);
    color = mix(grayscale, color, saturation);
    clampColor(color);

    FragColor = vec4(color, 1.0);
}