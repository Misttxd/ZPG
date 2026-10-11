#include "../Include/Transformations/Transformation.h"

#include "../Include/Transformations/Translation.hpp"
#include "../Include/Transformations/Rotation.hpp"
#include "../Include/Transformations/Scale.hpp"

#include <stdexcept>
#include <utility>

void Transformation::translate(float x, float y, float z, float speedX, float speedY, float speedZ)
{
    add(std::make_unique<Translation>(x, y, z, speedX, speedY, speedZ));
}

void Transformation::rotate(float degrees, float x, float y, float z, float degreesPerSecond)
{
    add(std::make_unique<Rotation>(degrees, x, y, z, degreesPerSecond));
}

void Transformation::scale(float x, float y, float z, float speedX, float speedY, float speedZ)
{
    add(std::make_unique<Scale>(x, y, z, speedX, speedY, speedZ));
}

void Transformation::scale(float value)
{
    scale(value, value, value);
}

void Transformation::add(std::unique_ptr<ITransformation> operation)
{
    if (!operation)
    {
        throw std::invalid_argument("Transformation cannot contain a null operation.");
    }
    operations.push_back(std::move(operation));
}

void Transformation::add(Transformation group)
{
    add(std::make_unique<Transformation>(std::move(group)));
}

void Transformation::clear()
{
    operations.clear();
}

glm::mat4 Transformation::getMatrix(double time) const
{
    glm::mat4 matrix(1.0f);
    for (const auto& operation : operations)
    {
        matrix = matrix * operation->getMatrix(time);
    }
    return matrix;
}
