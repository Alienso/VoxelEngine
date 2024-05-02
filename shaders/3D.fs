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
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;


    /*float fogDensity = 0.05;
    vec4 fogColor = vec4(0.2,0.2,0.2,0.5);
    const float LOG2 = 1.442695;
    float z = gl_FragCoord.z / gl_FragCoord.w;
    float fogFactor = exp2( -fogDensity *
                       fogDensity *
                       z *
                       z *
                       LOG2 );
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    vec4 finalColor = vec4(ambient + diffuse + specular, 1.0) * texture(texture1, TexCoord);
    FragColor = mix(fogColor, finalColor, fogFactor );*/


    FragColor = vec4(ambient + diffuse + specular, 1.0) * texture(texture1, TexCoord);
}