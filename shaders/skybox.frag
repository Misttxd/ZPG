#version 330 core

in vec3 TexCoord;
out vec4 FragColor;

uniform samplerCube textureUnitID;

void main()
{
    FragColor = texture(textureUnitID, TexCoord);
}