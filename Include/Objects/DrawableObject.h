#pragma once

#include "../Shaders/ShaderProgram.h"
#include "../Transformations/Transformation.h"
#include <memory>

class Model;

class DrawableObject
{
public:
	Transformation transformation;

	DrawableObject(const std::shared_ptr<Model>& model, ShaderProgram& shaderProgram);

	void draw(double time = 0.0);
	
private:
	std::shared_ptr<Model> model;
	ShaderProgram& shaderProgram;
};
