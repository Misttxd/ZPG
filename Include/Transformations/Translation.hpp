#pragma once

#include "ITransformation.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Translation : public ITransformation
{
public:
	Translation(float x = 0.0f, float y = 0.0f, float z = 0.0f, float speedX = 0.0f, float speedY = 0.0f, float speedZ = 0.0f) : position(x, y, z), speed(speedX, speedY, speedZ) {
	}

	glm::mat4 getMatrix(double time = 0.0) const override {
		return glm::translate(glm::mat4(1.0f), position + speed * static_cast<float>(time));
	}

private:
	glm::vec3 position;
	glm::vec3 speed;
};
