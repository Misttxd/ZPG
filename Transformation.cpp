#include "Transformation.h"

#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

void Transformation::translate(float x, float y, float z)
{
    matrix = glm::translate(matrix, glm::vec3(x, y, z));
}

void Transformation::rotate(float degrees, float x, float y, float z)
{
    glm::vec3 axis(x, y, z);
    if (glm::dot(axis, axis) == 0.0f)
    {
        throw std::invalid_argument("Rotation axis must be non-zero.");
    }

    matrix = glm::rotate(matrix, glm::radians(degrees), axis);
}

void Transformation::scale(float x, float y, float z)
{
    matrix = glm::scale(matrix, glm::vec3(x, y, z));
}

void Transformation::clear()
{
    matrix = glm::mat4(1.0f);
}

glm::mat4 Transformation::getMatrix() const
{
    return matrix;
}
