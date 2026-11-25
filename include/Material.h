#pragma once
#include <glm/vec3.hpp>

class Material
{
public:
    glm::vec3 color = glm::vec3(1.0f);
    glm::vec3 ambient = glm::vec3(0.03f);
    float specularStrength = 0.5f;
    float shininess = 32.0f;
};
