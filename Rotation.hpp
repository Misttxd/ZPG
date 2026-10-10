#pragma once

#include "ITransformation.hpp"

class Rotation : public ITransformation
{
public:
	Rotation(float degrees = 0.0f, float x = 0.0f, float y = 1.0f, float z = 0.0f) {
		matrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), glm::vec3(x,y,z));
	}
	glm::mat4 getMatrix() const override{
		return matrix;
	}

private:
	glm::mat4 matrix;
};


//CURRENTLY UNUSED 