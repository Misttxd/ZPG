#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 color;

out vec3 vertexColor;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

const vec3 palette[8] = vec3[8](
    vec3(0.6),                         // 0: číslice a rámeček
    vec3(1.0, 0.0, 0.0),              // 1: sekundová
    vec3(0.0),                         // 2: minutová
    vec3(5.0, 195.0, 222.0) / 255.0,   // 3: logo KI
    vec3(0.0),                         // 4: hodinová
    vec3(0.0),                         // 5: nepoužité
    vec3(0.0),                         // 6: nepoužité
    vec3(1.0)                          // 7: ciferník
);

uniform float time = 0.0; // sekundy od 12:00

const float degreesPerSecond[8] = float[8](
    0.0,
    6.0,         // sekundová: 360° za 60 sekund
    0.1,         // minutová: 360° za 3600 sekund
    0.0,
    1.0 / 120.0, // hodinová: 360° za 12 hodin
    0.0,
    0.0,
    0.0
);

void main()
{
    int part = int(color.r) + 2 * int(color.g) + 4 * int(color.b);
    vertexColor = palette[part];

    float angle = radians(-mod(time * degreesPerSecond[part], 360.0));

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