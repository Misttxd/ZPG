#include "../../Include/Objects/DrawableObject.h"
#include "../../Include/Models/Model.h"

#include <stdexcept>

DrawableObject::DrawableObject(const std::shared_ptr<Model>& model, ShaderProgram& shaderProgram):  model(model), shaderProgram(shaderProgram)
{
	if (!model)
	{
		throw std::invalid_argument("DrawableObject must have a model.");
	}
}

void DrawableObject::draw(double time)
{
	shaderProgram.setUniform("modelMatrix", transformation.getMatrix(time));

	model->draw();
}
