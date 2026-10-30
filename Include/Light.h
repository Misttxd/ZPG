#pragma once
#include <glm/vec3.hpp>

class Light
{
public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 color = glm::vec3(1.0f);
    glm::vec3 attenuationFactors = glm::vec3(1.0f, 0.0f, 0.0f);
};
