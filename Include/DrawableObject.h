#pragma once

#include "ShaderProgram.h"
#include "Transformation.h"
#include "Material.h"
#include <memory>

class Model;

class DrawableObject
{
public:
	Transformation transformation;
	Material material;

	DrawableObject(const std::shared_ptr<Model>& model, ShaderProgram& shaderProgram);

	void draw(double time = 0.0);

	bool alwaysOnTop = false;
	
private:
	std::shared_ptr<Model> model;
	ShaderProgram& shaderProgram;
};
