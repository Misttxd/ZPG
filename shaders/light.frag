#version 330 core

in vec4 worldPosition;
in vec3 worldNormal;

uniform vec3 objectColor;
uniform vec3 lightPosition;

out vec4 out_Color;
void main(void){
   
   vec3 lightToVector = lightPosition -vec3(worldPosition.x, worldPosition.y, worldPosition.z) ;


    float dotProduct = max(dot(normalize(lightToVector), normalize(worldNormal)), 0.0);

    vec4 diffuse = dotProduct * vec4( objectColor,1.0);
    vec4 ambient = vec4( 0.0, 0.0, 0.0, 1.0);
    out_Color = ambient + diffuse;

}