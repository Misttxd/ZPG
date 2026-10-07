#include "Transformation.h"

#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation() : translationX(0.0f), translationY(0.0f), translationZ(0.0f), scale(1.0f), rotation(0.0f)
{
}

void Transformation::setTranslation(float x, float y, float z)
{
	translationX = x;
	translationY = y;
	translationZ = z;
}

void Transformation::setScale(float scale)
{
	this->scale = scale;
}

void Transformation::setRotation(float rotation)
{
	this->rotation = rotation;
}

void Transformation::rotate(float angle)
{
	rotation += angle;
}

void Transformation::apply(ShaderProgram* shaderProgram)
{
    shaderProgram->setUniform("modelMatrix", calculateMatrix());
}

void Transformation::add(const Transformation& transformation)
{
    transformations.push_back(transformation);
}

void Transformation::setRotationAxis(float x, float y, float z)
{
    glm::vec3 axis(x, y, z);

    if (glm::length(axis) > 0.0f)
    {
        rotationAxis = glm::normalize(axis);
    }
}

void Transformation::setRotationSpeed(float speed)
{
    rotationSpeed = speed;
}

void Transformation::update(float deltaTime)
{
    rotate(rotationSpeed * deltaTime);

    for (Transformation& transformation : transformations)
    {
        transformation.update(deltaTime);
    }
}

glm::mat4 Transformation::calculateMatrix() const
{
    glm::mat4 M = glm::mat4(1.0f);

    M = glm::translate(M, glm::vec3(translationX, translationY, translationZ));
    M = glm::rotate(M, rotation, rotationAxis);
    M = glm::scale(M, glm::vec3(scale));

    for (const Transformation& transformation : transformations)
    {
        M = M * transformation.calculateMatrix();
    }

    return M;
}