#pragma once
#include <glm/vec3.hpp>

class Light
{
public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 color = glm::vec3(1.0f);
    glm::vec3 attenuationFactors = glm::vec3(1.0f, 0.0f, 0.0f);

    enum Type
    {
        Point,       // 0
        Directional, // 1
        SpotLight    // 2
    };

    static Light point(const glm::vec3& position, const glm::vec3& color, const glm::vec3& attenuation)
    {
        Light light;
        light.type = Point;
        light.position = position;
        light.color = color;
        light.attenuationFactors = attenuation;
        return light;
    }

    static Light directional(const glm::vec3& direction, const glm::vec3& color)
    {
        Light light;
        light.type = Directional;
        light.direction = direction;
        light.color = color;
        return light;
    }

    static Light spot(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color, const glm::vec3& attenuation)
    {
        Light light = point(position, color, attenuation);
        light.type = SpotLight;
        light.direction = direction;
        return light;
    }

    Type type = Point;
    glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
};
