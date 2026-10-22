#version 330 core

in vec3 vertexColor;

out vec4 out_Color;

void main(void)
{
    out_Color = vec4(vertexColor, 1.0);
}
