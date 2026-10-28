#version 330 core

in vec4 worldPosition;
in vec3 worldNormal;

uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

uniform vec3 attenuationFactors = vec3(1.0, 0.0, 0.0); //n

out vec4 out_Color;


float attenuation(float d, float c, float l, float q)
    {
        // d = distance from the light to the fragment
        // c = constant attenuation factor
        // l = linear attenuation factor
        // q = quadratic attenuation factor
        float att=1.0/ (c + l*d + q*d*d);
        return clamp(att , 0.0 , 1.0);
    }

void main(void)
{
    

    vec3 lightToVector = lightPosition - worldPosition.xyz;

//    float att = attenuation(length(lightToVector), 1.0, 0.0, 0.0);

    float att = attenuation(
    length(lightToVector),
    attenuationFactors.x,
    attenuationFactors.y,
    attenuationFactors.z
);

    vec3 N = normalize(worldNormal);
    vec3 L = normalize(lightToVector);
    vec3 V = normalize(cameraPosition - worldPosition.xyz);

    float dotProduct = max(dot(N, L), 0.0);

    vec4 ambient = vec4(0.03, 0.03, 0.03, 1.0);
    vec4 diffuse = dotProduct * vec4(objectColor, 1.0);


    float spec = 0.0;

    if (dotProduct > 0.0)
    {
        vec3 R = reflect(-L, N);
        spec = pow(max(dot(R, V), 0.0), 32.0);
    }

    vec4 specular = vec4(vec3(0.5 * spec), 0.0);

    out_Color = vec4((ambient + att * (diffuse + specular)).rgb, 1.0);
}
