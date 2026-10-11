#include "DrawableObject.h"

DrawableObject::DrawableObject(Model& model, ShaderProgram* shaderProgram) : model(model), shaderProgram(shaderProgram) {}

void DrawableObject::draw(double time)
{
	shaderProgram->setUniform("modelMatrix", transformation.getMatrix(time));

	model.draw();
}
