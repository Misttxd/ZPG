#version 330 core

out vec4 FragColor;

uniform vec3 fragmentColor = vec3(1.0, 1.0, 0.0);

void main()
{
    FragColor = vec4(fragmentColor, 1.0);
}