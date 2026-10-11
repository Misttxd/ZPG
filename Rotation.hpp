#pragma once

#include "ITransformation.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <stdexcept>

class Rotation : public ITransformation
{
public:
	Rotation(float degrees = 0.0f, float x = 0.0f, float y = 1.0f, float z = 0.0f, float degreesPerSecond = 0.0f) : degrees(degrees), axis(x, y, z), degreesPerSecond(degreesPerSecond) {
		if (x == 0.0f && y == 0.0f && z == 0.0f) {
			throw std::invalid_argument("Rotation axis must not be zero.");
		}
		axis = glm::normalize(axis);
	}

	glm::mat4 getMatrix(double time = 0.0) const override {
		float angle = static_cast<float>(std::fmod(degrees + degreesPerSecond * time, 360.0));
		return glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
	}

private:
	float degrees;
	glm::vec3 axis;
	float degreesPerSecond;
};
