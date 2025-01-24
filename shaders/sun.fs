#version 460 core

out vec4 FragColor;

uniform vec3 lightColor;

void main(){
    /*vec2 uv = gl_FragCoord.xy/uResolution * 2.0 - vec2(1);
	if ((uv.x - lightPos.x)*(uv.x - lightPos.x) + (uv.y - lightPos.y)*(uv.y - lightPos.y) < 0.2)
            FragColor = vec4(1.0,1.0,1.0,1.0);
    else discard;*/
    FragColor = vec4(lightColor, 1.0);
}