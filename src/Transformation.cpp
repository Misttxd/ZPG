#include "Transformation.h"

#include "Translation.hpp"
#include "Rotation.hpp"
#include "Scale.hpp"
#include "PathTransformation.hpp"

#include <stdexcept>
#include <utility>

void Transformation::translate(float x, float y, float z, float speedX, float speedY, float speedZ)
{
    add(std::make_unique<Translation>(x, y, z, speedX, speedY, speedZ));
}

void Transformation::setPosition(const glm::vec3& position)
{
    auto* translation = dynamic_cast<Translation*>(operations.front().get());

    translation->setCoords(position);
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

void Transformation::moveBezier(float duration)
{
    if (path == nullptr)
    {
        auto operation = std::make_unique<PathTransformation>();
        path = operation.get();
        add(std::move(operation));
    }

    path->begin(duration);
}

bool Transformation::addPathPoint(const glm::vec3& point, double time)
{
    if (path == nullptr)
    {
        return false;
    }

    return path->addPoint(point, time);
}

const std::vector<glm::vec3>& Transformation::getPathPoints() const
{
    return path->getPoints();
}

void Transformation::setPathPoint(int index, const glm::vec3& point)
{
    path->setPoint(index, point);
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
    path = nullptr;
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
