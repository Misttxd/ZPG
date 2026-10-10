#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject
{
public:
	Transformation transformation;

	DrawableObject(Model& model, ShaderProgram* shaderProgram);

	void draw();
	
private:
	Model& model;
	ShaderProgram* shaderProgram;
};
