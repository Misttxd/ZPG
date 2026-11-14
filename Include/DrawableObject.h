#pragma once

#include "ShaderProgram.h"
#include "Transformation.h"
#include "Material.h"
#include <memory>

class Model;
enum class ObjectType;

class DrawableObject
{
public:
	Transformation transformation;
	Material material;
	ObjectType type{};
	glm::vec3 positionOffset{0.0f};

	GLuint texture = 0;
	int textureUnit = 0;
	GLenum textureTarget = GL_TEXTURE_2D;

	DrawableObject(const std::shared_ptr<Model>& model, ShaderProgram& shaderProgram);

	void draw(double time = 0.0);
	void drawOutline(ShaderProgram& program, double time);

	int getId();
	void setId(int newId);

	bool alwaysOnTop = false;
	
private:
	int id;

	glm::mat4 getModelMatrix(double time) const;
	std::shared_ptr<Model> model;
	ShaderProgram& shaderProgram;
	
};
