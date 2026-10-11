#pragma once

#include "ITransformation.hpp"

#include <memory>
#include <vector>

class Transformation : public ITransformation {
public:
    void translate(float x, float y, float z, float speedX = 0.0f, float speedY = 0.0f, float speedZ = 0.0f);
    void rotate(float degrees, float x, float y, float z, float degreesPerSecond = 0.0f);
    void scale(float x, float y, float z, float speedX = 0.0f, float speedY = 0.0f, float speedZ = 0.0f);
    void scale(float value);

    void add(std::unique_ptr<ITransformation> operation);
    void add(Transformation group);

    void clear();
    glm::mat4 getMatrix(double time = 0.0) const override;

private:
    std::vector<std::unique_ptr<ITransformation>> operations;
};

