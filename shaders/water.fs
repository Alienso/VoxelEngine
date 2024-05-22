#version 460 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

layout(binding=0) uniform sampler2D texture1;

uniform vec3 lightColor;
uniform vec3 lightDir;
uniform vec3 viewPos;

uniform float ambientStrength;
uniform float specularStrength;
uniform int shininess;

void main(){

    //vec4 texColor = texture(texture1, TexCoord);
    vec4 texColor = vec4(0.1,0.3,0.8,0.25);
    FragColor = texColor;

    /*vec3 ambient = 0.1 * lightColor;

    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 finalColor = ambient + diffuse + specular;
    clampColor(finalColor);
    FragColor = vec4(finalColor, 0.5) * texColor;*/
}