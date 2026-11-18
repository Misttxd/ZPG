#version 330 core

in vec4 worldPosition;
in vec3 worldNormal;

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
uniform vec3 lightAttenuations[MAX_LIGHTS];

out vec4 out_Color;

float attenuation(float d, float c, float l, float q)
{
    float att = 1.0 / (c + l*d + q*d*d);
    return clamp(att, 0.0, 1.0);
}

void main(void)
{
    vec3 N = normalize(worldNormal);
    vec3 V = normalize(cameraPosition - worldPosition.xyz);

    vec4 ambient = vec4(materialAmbient, 1.0);
    vec4 result = ambient;

    for (int i = 0; i < numberOfLights; i++)
    {
        vec3 lightToVector = lights[i].position.xyz - worldPosition.xyz;
        vec3 L = normalize(lightToVector);

        float dotProduct = max(dot(N, L), 0.0);
        vec4 diffuse = dotProduct * vec4(objectColor, 1.0);

        float spec = 0.0;
        if (dotProduct > 0.0)
        {
            vec3 R = reflect(-L, N);
            spec = pow(max(dot(R, V), 0.0), shininess);
        }
        vec4 specular = vec4(vec3(specularStrength * spec), 0.0);

        float att = attenuation(length(lightToVector), lightAttenuations[i].x, lightAttenuations[i].y, lightAttenuations[i].z);
        result += att * (lights[i].diffuse * diffuse + lights[i].specular * specular);
    }

    out_Color = vec4(result.rgb, 1.0);
}
