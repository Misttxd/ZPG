#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 worldPosition;
out vec3 worldNormal;
out vec3 vertexColor;

void main()
{
    worldPosition = modelMatrix * vec4(position, 1.0);
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNormal = normalMatrix * vertexNormal;

    // The same trunk/crown split as in TreeShader.vert.
    if (gl_VertexID > 36443)
        vertexColor = vec3(0.12, 0.5, 0.08);
    else
        vertexColor = vec3(0.35, 0.18, 0.06);

    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
