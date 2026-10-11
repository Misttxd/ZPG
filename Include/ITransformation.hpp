#pragma once

#include <glm/mat4x4.hpp>

class ITransformation {
public:
    virtual glm::mat4 getMatrix(double time = 0.0) const = 0;
    virtual ~ITransformation() = default;
};
