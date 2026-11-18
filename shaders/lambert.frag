#version 330 core

in vec4 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

uniform vec3 objectColor;
uniform vec3 materialAmbient;

// Stejne prepinace barev jako ve spolecnem Phongove shaderu.
uniform bool isTree = false;
uniform bool useVertexColor = false;

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
    // d = distance from the light to the fragment
    // c = constant attenuation factor
    // l = linear attenuation factor
    // q = quadratic attenuation factor
    float att = 1.0 / (c + l*d + q*d*d);
    return clamp(att, 0.0, 1.0);
}

void main(void)
{
    vec3 N = normalize(worldNormal);

    vec4 ambient = vec4(materialAmbient, 1.0);
    vec4 result = ambient;

    for (int index = 0; index < numberOfLights; index++)
    {
        int type = int(lights[index].direction.w); // direction.xyz = directions | direction.w = enum type
        vec3 lightToVector = lights[index].position.xyz - worldPosition.xyz;

        if (type == 1) // smerove
        {
            lightToVector = -lights[index].direction.xyz;
        }

        vec3 L = normalize(lightToVector);

        float dotProduct = max(dot(N, L), 0.0);
        vec4 diffuse = dotProduct * vec4(objectColor, 1.0);

        if (isTree || useVertexColor)
        {
            diffuse = dotProduct * vec4(vertexColor * objectColor, 1.0);
        }
        if (type == 2) // reflektor
        {
            float spot = dot(normalize(lights[index].direction.xyz), -L);

            float alpha = 0.98; // no light
            //between = smooth transition
            float beta = 0.995; // yes light

            float intens = clamp((spot - alpha) / (beta - alpha), 0.0, 1.0);

            diffuse *= intens;
        }

        float att = 1.0;

        if (type == 1) // smerove
        {
            att = 1.0;
        }
        else if (type == 0 || type == 2) // bodove nebo reflektor
        {
            att = attenuation(length(lightToVector), lightAttenuations[index].x, lightAttenuations[index].y, lightAttenuations[index].z);
        }

        result += att * lights[index].diffuse * diffuse;
    }

    out_Color = vec4(result.rgb, 1.0);
}
