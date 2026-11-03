#version 330 core

in vec3 TexCoord;
out vec4 FragColor;

uniform sampler2D textureUnitID;

void main()
{
    vec3 direction = normalize(TexCoord);

    const float pi = 3.14159265;
    float u = atan(direction.z, direction.x) / (2.0 * pi) + 0.5;
    float v = asin(clamp(direction.y, -1.0, 1.0)) / pi + 0.5;

    FragColor = texture(textureUnitID, vec2(u, v));
}