#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 vn;

out vec4 worldPosition;
out vec3 vertexColor;
out vec3 worldNormal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main(void)
{
    vertexColor = color;

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp,1.0f);
    worldPosition = modelMatrix * vec4(vp,1.0f);
    worldNormal = mat3(modelMatrix)*vn;
}