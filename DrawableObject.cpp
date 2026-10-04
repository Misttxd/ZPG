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