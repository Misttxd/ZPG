#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* newModel, ShaderProgram* newShaderProgram) : model(newModel),	shaderProgram(newShaderProgram)
{
}

void DrawableObject::draw()
{
	shaderProgram->use();
	model->draw();	
}