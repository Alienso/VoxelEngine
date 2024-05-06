#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aAo;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 AO;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);

	switch(int(aAo)){
	    case 0:
	        AO = vec3(0.75,0.75,0.75);
	        break;
	    case 1:
	        AO = vec3(0.5,0.5,0.5);
	        break;
        case 2:
	        AO = vec3(0.25,0.25,0.25);
	        break;
	    case 3:
        	AO = vec3(0.0,0.0,0.0);
        	break;
	}
}