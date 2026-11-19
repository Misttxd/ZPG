#version 330 core

in vec4 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;
in vec2 uv;

uniform bool useTexture = false;
uniform sampler2D textureUnitID;

uniform vec3 objectColor;
uniform vec3 materialAmbient;
uniform vec3 cameraPosition;
uniform float specularStrength;
uniform float shininess;

uniform float alpha;
uniform float beta;


uniform bool isTree = false;

uniform bool useVertexColor = false;

#define MAX_LIGHTS 20
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
    vec3 V = normalize(cameraPosition - worldPosition.xyz);

    vec3 surfaceColor = objectColor;
    vec4 ambient = vec4(materialAmbient, 1.0);
    if (useTexture)
    {
        vec3 texel = texture(textureUnitID, uv).rgb;
        surfaceColor *= texel;
        ambient.rgb *= texel;
    }
    vec4 result = ambient;

    for (int i = 0; i < numberOfLights; i++)
    {
        int type = int(lights[i].direction.w); // direction.xyz = directions | direction.w = enum type
        vec3 lightToVector = lights[i].position.xyz - worldPosition.xyz;

        if (type == 1) // smerove
        {
            lightToVector = -lights[i].direction.xyz;
        }

        vec3 L = normalize(lightToVector);

        float dotProduct = max(dot(N, L), 0.0);
        vec4 diffuse = dotProduct * vec4(surfaceColor, 1.0);

        if (isTree || useVertexColor) // Strom nebo model s vlastni barvou vrcholu
        {
            diffuse = dotProduct * vec4(vertexColor * surfaceColor, 1.0);
        }

        float spec = 0.0;
        if (dotProduct > 0.0)
        {
            vec3 R = reflect(-L, N);
            spec = pow(max(dot(R, V), 0.0), shininess);
        }


//        if (type == 2) // reflektor sharp edge
//        {
//            float spot = dot(normalize(lights[i].direction.xyz), -L);
//            if (spot < 0.99)
//            {
//                spec = 0.0;
//                diffuse = vec4(0.0);
//            }
//        }

        if (type == 2) // reflektor
        {
            float spot = dot(normalize(lights[i].direction.xyz), -L);

//            float alpha = 0.87+0.03; // no light
//            //between = smooth transition
//            float beta = 0.92+0.03; // yes light

            float intens = clamp((spot - alpha) / (beta - alpha), 0.0, 1.0);

            spec *= intens;
            diffuse *= intens;
        }

        vec4 specular = vec4(vec3(specularStrength * spec), 0.0);

        float att = 1.0;

        if (type == 1) // smerove
        {
            att = 1.0;
        }
        else if (type == 0 || type == 2) // bodove nebo reflektor
        {
            att = attenuation(length(lightToVector), lightAttenuations[i].x, lightAttenuations[i].y, lightAttenuations[i].z);
        }

        result += att * (lights[i].diffuse * diffuse + lights[i].specular * specular);
    }

    out_Color = vec4(result.rgb, 1.0);
}
