#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject
{
public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram);

	void draw();

	void setTransformation(const Transformation& transformation);
	void setRotation(float rotation);

private:
	Model* model;
	ShaderProgram* shaderProgram;
	Transformation transformation;
};