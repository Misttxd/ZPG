#version 330 core

in vec4 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

uniform vec3 objectColor;
uniform vec3 materialAmbient;

#define MAX_LIGHTS 4
struct Light
{
    vec4 position;
    vec4 diffuse;
    vec4 specular;
    vec4 direction;
};

layout(std140) uniform LightBuffer
{
    Light lights[MAX_LIGHTS];
};
uniform int numberOfLights;

out vec4 out_Color;

void main(void)
{
    vec3 N = normalize(worldNormal);

    vec4 ambient = vec4(materialAmbient, 1.0);
    vec4 result = ambient;

    for (int index = 0; index < numberOfLights; index++)
    {
        vec3 lightToVector = lights[index].position.xyz - worldPosition.xyz;
        vec3 L = normalize(lightToVector);

        float dotProduct = max(dot(N, L), 0.0);
        vec4 diffuse = dotProduct * vec4(vertexColor * objectColor, 1.0);
        result += lights[index].diffuse * diffuse;
    }

    out_Color = vec4(result.rgb, 1.0);
}
