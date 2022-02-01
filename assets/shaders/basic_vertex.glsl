#version 430 core

layout(location = 0) in vec4 pos;

uniform mat4 proj;
uniform mat4 cam;

void main() { gl_Position = proj * cam * pos; }