#pragma once

#include "ITransformation.hpp"

class Translation : public ITransformation
{
public:
	Translation(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
		matrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	}

	glm::mat4 getMatrix() const override {
		return matrix;
	}

private:
	glm::mat4 matrix;
};