#include "DrawableObject.h"

DrawableObject::DrawableObject(Model& model, ShaderProgram* shaderProgram) : model(model), shaderProgram(shaderProgram) {}

void DrawableObject::draw()
{
	shaderProgram->setUniform("modelMatrix", transformation.getMatrix());

	model.draw();
}
