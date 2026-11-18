#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec3 colorNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform bool isTree = false;
uniform bool useVertexColor = false;

out vec4 worldPosition;
out vec3 worldNormal;
out vec3 vertexColor;

void main(void)
{
    worldPosition = modelMatrix * vec4(vp, 1.0);
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNormal = normalMatrix * vn;

    if (useVertexColor) // Model ma na location 1 barvu a na location 2 normalu.
    {
        worldNormal = normalMatrix * colorNormal;
    }

    if (isTree) 
    {
        // Procedurální rozdělení koruny a kmene podle indexu vrcholu
        if(gl_VertexID>36443)   
        {
            vertexColor = vec3(0.12, 0.50, 0.08);
        }
        else 
        {
            vertexColor = vec3(0.35, 0.18, 0.06);
        }

    } 
    else if (useVertexColor) // Barva ulozena primo ve vrcholech modelu.
    {
        vertexColor = vn;
    }
    else {
        vertexColor = vec3(1.0);
    }

    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
