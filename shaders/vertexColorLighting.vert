#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 worldPosition;
out vec3 worldNormal;
out vec3 vertexColor;

void main(void)
{
    worldPosition = modelMatrix * vec4(vp, 1.0);
    worldNormal = mat3(modelMatrix) * vn;
    vertexColor = color;
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
