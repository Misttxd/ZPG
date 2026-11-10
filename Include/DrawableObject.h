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

	GLuint texture = 0;
	int textureUnit = 0;
	GLenum textureTarget = GL_TEXTURE_2D;

	DrawableObject(const std::shared_ptr<Model>& model, ShaderProgram& shaderProgram);

	void draw(double time = 0.0);

	int getId();
	void setId(int newId);

	bool alwaysOnTop = false;
	
private:
	std::shared_ptr<Model> model;
	ShaderProgram& shaderProgram;
	int id;
};
