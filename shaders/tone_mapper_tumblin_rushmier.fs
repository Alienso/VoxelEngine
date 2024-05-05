#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding=0) uniform sampler2D luminanceTexture;
layout(binding=1) uniform sampler2D renderTexture;

uniform float lumMax;
uniform float cMax;

void main(){
    vec3 color = texture(renderTexture, TexCoords).rgb;
    vec3 Cout = vec3((color * (2.51*color + 0.03)) / (color * (2.43*color + 0.59) + 0.14));

    /*float lumIn = 0.2126*color.r + 0.7152*color.g + 0.0722*color.b;
    float lumAvg = textureLod(luminanceTexture, vec2(0,0), 10.0).r;

    float logLrw = log(lumAvg) / log(10) + 0.84;
    float alphaRw = 0.4 * logLrw + 2.92;
    float betaRw = -0.4 * logLrw * logLrw - 2.584 * logLrw + 2.0208;

    float Lwd = lumMax / sqrt(cMax);
    float logLd = log(Lwd) / log(10) + 0.84;
    float alphaD = 0.4 * logLd + 2.92;
    float betaD = -0.4 * logLd * logLd - 2.584 * logLd + 2.0208;

    float lumOut = pow(lumIn, alphaRw / alphaD) / lumMax * pow(10, (betaRw / betaD) / alphaD) - (1.0 / cMax);
    vec3 Cout = color / lumIn * lumOut;*/

    FragColor = vec4(Cout, 1.0);
}