#version 330 core

in vec2 uv;
out vec4 FragColor;

uniform sampler2D textureUnitID;



void main()
{
    //FragColor = vec4(uv, 1.0, 1.0);
    FragColor = texture(textureUnitID, uv);
}