#version 330 core

uniform vec3 objectColor;

out vec4 out_Color;

void main(void)
{
    out_Color = vec4(objectColor, 1.0);
}
