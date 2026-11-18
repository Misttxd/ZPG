#version 330 core

in vec3 vertexColor;

uniform vec3 objectColor;
uniform bool isTree = false;
uniform bool useVertexColor = false;

out vec4 out_Color;

void main(void)
{
    out_Color = vec4(objectColor, 1.0);

    if (isTree || useVertexColor) // Stejny vyber barvy jako u ostatnich modelu.
    {
        out_Color = vec4(vertexColor * objectColor, 1.0);
    }
}
