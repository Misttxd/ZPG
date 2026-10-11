#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject
{
public:
	Transformation transformation;

	DrawableObject(Model& model, ShaderProgram* shaderProgram);

	void draw(double time = 0.0);
	
private:
	Model& model;
	ShaderProgram* shaderProgram;
};
