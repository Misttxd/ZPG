#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 color;

out vec3 vertexColor;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform float time = 0.0; //seconds since 12:00

void main()
{
    vertexColor = color;
    float degreesPerSecond = 0.0;

    if (color == vec3(1.0, 1.0, 0.0)) //yellow: KI logo
    {
        vertexColor = vec3(5.0, 195.0, 222.0) / 255.0;
    }
    else if (color == vec3(1.0, 0.0, 0.0)) //red: second hand
    {
        degreesPerSecond = 6.0;
    }
    else if (color == vec3(0.0, 1.0, 0.0)) //green: minute hand
    {
        vertexColor = vec3(0.0);
        degreesPerSecond = 0.1;
    }
    else if (color == vec3(0.0, 0.0, 1.0)) //blue: hour hand
    {
        vertexColor = vec3(0.0);
        degreesPerSecond = 1.0 / 120.0;
    }
    else if (color == vec3(0.0)) //black: numerals and frame
    {
        vertexColor = vec3(0.6);
    }

    float angle = radians(-time * degreesPerSecond);

    float c = cos(angle);
    float s = sin(angle);

    mat2 rotation = mat2(
         c, s,
        -s, c
    );

    vec3 rotatedPosition = position;
    rotatedPosition.xy = rotation * position.xy;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(rotatedPosition, 1.0);
}
