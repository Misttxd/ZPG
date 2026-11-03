#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 TexCoord;

void main()
{
    TexCoord = vertexPosition;
    gl_Position = projectionMatrix * mat4(mat3(viewMatrix)) * modelMatrix * vec4(vertexPosition, 1.0);
}