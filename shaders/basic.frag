#version 330 core

in vec3 vertexColor;
out vec4 FragColor;
uniform vec3 baseColor;

void main()
{
    float shade = 0.45 + 0.55 * abs(vertexColor.y);
    FragColor = vec4(baseColor * shade, 1.0);
}
