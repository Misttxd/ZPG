#include "DrawableObject.h"
#include "Model.h"

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
	shaderProgram.setMaterial(material);

	bool restoreDepthTest = alwaysOnTop && glIsEnabled(GL_DEPTH_TEST);

	if (alwaysOnTop)
	{
		glDisable(GL_DEPTH_TEST);
	}

	if (texture != 0)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		//glBindTexture(GL_TEXTURE_2D, texture);
		glBindTexture(textureTarget, texture);
		shaderProgram.setUniformInt("textureUnitID", textureUnit);
	}

	model->draw();

	if (restoreDepthTest)
	{
		glEnable(GL_DEPTH_TEST);
	}
}


