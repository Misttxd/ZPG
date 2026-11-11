#include "DrawableObject.h"
#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

DrawableObject::DrawableObject(const std::shared_ptr<Model>& model, ShaderProgram& shaderProgram):  model(model), shaderProgram(shaderProgram), id(0)
{
	if (!model)
	{
		throw std::invalid_argument("DrawableObject must have a model.");
	}
}

void DrawableObject::draw(double time)
{
	shaderProgram.setUniform("modelMatrix", getModelMatrix(time));
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

glm::mat4 DrawableObject::getModelMatrix(double time) const
{
	return glm::translate(glm::mat4(1.0f), positionOffset) * transformation.getMatrix(time);
}

void DrawableObject::drawOutline(ShaderProgram& program, double time)
{
	program.setUniform("modelMatrix", glm::scale(getModelMatrix(time), glm::vec3(1.06f)));
	program.setUniform("objectColor", 1.0f, 0.72f, 0.05f);
	model->draw();
}

int DrawableObject::getId()
{

	return this->id;
}

void DrawableObject::setId(int noveId)
{
	this->id = noveId;
}
