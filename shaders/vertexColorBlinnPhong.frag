#version 330 core

in vec4 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

uniform vec3 objectColor;
uniform vec3 materialAmbient;
uniform vec3 cameraPosition;
uniform float specularStrength;
uniform float shininess;

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
    vec3 V = normalize(cameraPosition - worldPosition.xyz);

    vec4 ambient = vec4(materialAmbient, 1.0);
    vec4 result = ambient;

    for (int index = 0; index < numberOfLights; index++)
    {
        vec3 lightToVector = lights[index].position.xyz - worldPosition.xyz;
        vec3 L = normalize(lightToVector);

        float dotProduct = max(dot(N, L), 0.0);
        vec4 diffuse = dotProduct * vec4(vertexColor * objectColor, 1.0);

        float spec = 0.0;
        if (dotProduct > 0.0)
        {
            vec3 H = normalize(L + V);
            spec = pow(max(dot(N, H), 0.0), shininess);
        }
        vec4 specular = vec4(vec3(specularStrength * spec), 0.0);
        result += lights[index].diffuse * diffuse + lights[index].specular * specular;
    }

    out_Color = vec4(result.rgb, 1.0);
}
