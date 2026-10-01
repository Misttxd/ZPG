#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;
uniform vec3 translation = vec3(0.0, 0.0, 0.0);
uniform float scale = 1.0f;
uniform float rotation = 0.0f;

void main()
{
    float x = cos(rotation) * position.x + sin(rotation) * position.z;
    float y = position.y;
    float z = -sin(rotation) * position.x + cos(rotation) * position.z;

    vec3 rotatedPosition = vec3(x, y, z);
    
    vertexColor = color;
    gl_Position = vec4(scale * rotatedPosition + translation, 1.0);
}