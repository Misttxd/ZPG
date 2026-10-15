#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexNormal;

out vec3 vertexColor;
out vec3 normal;

uniform mat4 modelMatrix = mat4(1.0);;
uniform mat4 viewMatrix = mat4(1.0);;
uniform mat4 projectionMatrix = mat4(1.0);;


void main()
{
    normal = vertexNormal;

    if(gl_VertexID>36443)   
    {
        vertexColor = vec3(0.f, 1.f, 0.f);
    }
    else vertexColor = vec3(1.f, 0.f, 0.f);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
