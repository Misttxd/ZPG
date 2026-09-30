#pragma once

#include "Model.h"
#include "ShaderProgram.h"

class DrawableObject
{
public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram);

	void draw();

private:
	Model* model;
	ShaderProgram* shaderProgram;
};