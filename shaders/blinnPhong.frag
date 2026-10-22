#version 330 core

in vec4 worldPosition;
in vec3 worldNormal;

uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

out vec4 out_Color;

void main(void)
{
    vec3 lightToVector = lightPosition - worldPosition.xyz;

    vec3 N = normalize(worldNormal);
    vec3 L = normalize(lightToVector);
    vec3 V = normalize(cameraPosition - worldPosition.xyz);

    float dotProduct = max(dot(N, L), 0.0);

    vec4 ambient = vec4(0.03, 0.03, 0.03, 1.0);
    vec4 diffuse = dotProduct * vec4(objectColor, 1.0);

    // Specular light is only evaluated on the side facing the light.
    float spec = 0.0;

    if (dotProduct > 0.0)
    {
        vec3 H = normalize(L + V);
        spec = pow(max(dot(N, H), 0.0), 32.0);
    }

    vec4 specular = vec4(vec3(0.5 * spec), 0.0);

    out_Color = ambient + diffuse + specular;
}
