#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;
uniform vec3 translation = vec3(0.5, 0.0, 0.0);
uniform float scale = 1.0f;

void main()
{
    
    vertexColor = color;
    gl_Position = vec4(scale * position + translation, 1.0);
}