#version 460 core

#define SCALE 2

layout (triangles) in;
layout (triangle_strip, max_vertices = SCALE*SCALE*3) out;

in VS_OUT {
    vec3 vPos;
    vec3 vNormal;
    vec2 vTexCoord;
    float vAo;
} gs_in[];

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

    /*if (gl_PrimitiveIDIn / 4 == 0 || gl_PrimitiveIDIn / 5 == 0 || gl_PrimitiveIDIn / 6 == 0) //discard second triangle
        return;

    float scaleFloat = float(SCALE);
    float step = 1.0 / SCALE;

    vec4 AB = gl_in[1].gl_Position - gl_in[0].gl_Position;
    vec4 AC = gl_in[2].gl_Position - gl_in[0].gl_Position;

    for (int i=0; i<SCALE; i++){
        for(int j=0; j<SCALE; j++){

            vec4 offset = vec4(j / scaleFloat, 0, i / scaleFloat, 1.0);
            vec4 offset2 = vec4((j + 1) / scaleFloat, 0, (i + 1) / scaleFloat, 1.0);

            gl_Position = projection * view * model * vec4(gl_in[0].gl_Position + offset * AB);
            FragPos = vec3(model * vec4(gs_in[0].vPos, 1.0));
            Normal = mat3(transpose(inverse(model))) * gs_in[0].vNormal;
            TexCoord = vec2(gs_in[0].vTexCoord.x, gs_in[0].vTexCoord.y);
            EmitVertex();

            gl_Position = projection * view * model * vec4(gl_in[0].gl_Position + offset2 * AC);
            FragPos = vec3(model * vec4(gs_in[1].vPos, 1.0));
            Normal = mat3(transpose(inverse(model))) * gs_in[1].vNormal;
            TexCoord = vec2(gs_in[1].vTexCoord.x, gs_in[1].vTexCoord.y);
            EmitVertex();

            gl_Position = projection * view * model * vec4(gl_in[0].gl_Position + offset * AB + offset * AC);
            FragPos = vec3(model * vec4(gs_in[2].vPos, 1.0));
            Normal = mat3(transpose(inverse(model))) * gs_in[2].vNormal;
            TexCoord = vec2(gs_in[2].vTexCoord.x, gs_in[2].vTexCoord.y);
            EmitVertex();

            EndPrimitive();
        }
    }*/

    gl_Position = projection * view * model * gl_in[0].gl_Position;
    FragPos = vec3(model * vec4(gs_in[0].vPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * gs_in[0].vNormal;
    TexCoord = vec2(gs_in[0].vTexCoord.x, gs_in[0].vTexCoord.y);
    EmitVertex();

    gl_Position = projection * view * model * gl_in[1].gl_Position;
    FragPos = vec3(model * vec4(gs_in[1].vPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * gs_in[1].vNormal;
    TexCoord = vec2(gs_in[1].vTexCoord.x, gs_in[1].vTexCoord.y);
    EmitVertex();

    gl_Position = projection * view * model * gl_in[2].gl_Position;
    FragPos = vec3(model * vec4(gs_in[2].vPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * gs_in[2].vNormal;
    TexCoord = vec2(gs_in[2].vTexCoord.x, gs_in[2].vTexCoord.y);
    EmitVertex();

    EndPrimitive();


    /*for (int x = 0; x < SCALE; ++x) {
        for (int y = 0; y < SCALE; ++y) {
            vec3 offset = vec3(float(x), 0, float(y));

            for (int i = 0; i < gl_in.length(); ++i) {
                gl_Position =  projection * view * model * ((gl_in[i].gl_Position + vec4(offset, 0.0)) / SCALE);
                EmitVertex();
            }

            EndPrimitive();
        }
     }*/
}