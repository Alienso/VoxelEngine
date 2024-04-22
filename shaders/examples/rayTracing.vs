#version 430 core
layout (location = 0) in vec2 aPos;

uniform float uTime;
uniform vec4 uMouse;
uniform vec2 uResolution;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
}