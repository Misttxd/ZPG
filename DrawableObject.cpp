#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* newModel, ShaderProgram* newShaderProgram) : model(newModel),	shaderProgram(newShaderProgram)
{
}

void DrawableObject::draw()
{
	shaderProgram->use();
	transformation.apply(shaderProgram);
	model->draw();
}

void DrawableObject::setTransformation(const Transformation& transformation)
{
	this->transformation = transformation;
}
void DrawableObject::setRotation(float rotation)
{
	transformation.setRotation(rotation);
}

void DrawableObject::setTranslation(float x, float y, float z)
{
	transformation.setTranslation(x, y, z);
}

void DrawableObject::setScale(float scale)
{
	transformation.setScale(scale);
}

void DrawableObject::setRotationSpeed(float speed)
{
	rotationSpeed = speed;
}

void DrawableObject::update(float deltaTime)
{
	transformation.rotate(rotationSpeed * deltaTime);
}
