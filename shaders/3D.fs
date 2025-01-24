#version 460 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 AO;

layout(binding=0) uniform sampler2D texture1;

uniform vec3 lightColor;
uniform vec3 lightDir;
uniform vec3 viewPos;

uniform float ambientStrength;
uniform float specularStrength;
uniform int shininess;

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

    vec4 texColor = texture(texture1, TexCoord);
    if (texColor.a < 0.1)
        discard;

    //vec3 ambient = ambientStrength * lightColor;
    vec3 ambient = AO * lightColor;

    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 finalColor = ambient + diffuse + specular;
    clampColor(finalColor);
    FragColor = vec4(finalColor, 1.0) * texColor;
}