#pragma once

#include "ITransformation.hpp"

class Scale : public ITransformation {


public:
    Scale(float x, float y, float z) 
    {
        matrix = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
    }
    Scale(float value = 1.0f)
    {
        matrix = glm::scale(glm::mat4(1.0), glm::vec3(value));
    }

    glm::mat4 getMatrix() const override {
        return matrix;
    }

private:
    glm::mat4 matrix;
};


//CURRENTLY UNUSED 