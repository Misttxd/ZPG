#pragma once

#include "ITransformation.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Scale : public ITransformation {
public:
    Scale(float x, float y, float z, float speedX = 0.0f, float speedY = 0.0f, float speedZ = 0.0f) : factors(x, y, z), speed(speedX, speedY, speedZ)
    {
    }

    Scale(float value = 1.0f) : Scale(value, value, value)
    {
    }

    glm::mat4 getMatrix(double time = 0.0) const override {
        return glm::scale(glm::mat4(1.0f), factors + speed * static_cast<float>(time));
    }

private:
    glm::vec3 factors;
    glm::vec3 speed;
};
