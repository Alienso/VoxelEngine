#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aAo;

out VS_OUT { //TODO remove normals and AO
    vec3 vPos;
    vec3 vNormal;
    vec2 vTexCoord;
    float vAo;
} vs_out;

void main(){
    vs_out.vPos = aPos;
    vs_out.vNormal = aNormal;
    vs_out.vTexCoord = aTexCoord;
    vs_out.vAo = aAo;
	gl_Position = vec4(aPos, 1.0f);
}