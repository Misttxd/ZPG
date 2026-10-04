#include "Transformation.h"

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
	shaderProgram->setUniform("translation", translationX, translationY, translationZ);
	shaderProgram->setUniform("scale", scale);
	shaderProgram->setUniform("rotation", rotation);
}
