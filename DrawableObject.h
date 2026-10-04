#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject
{
public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram);

	void draw();
	void update(float deltaTime);

	void setTransformation(const Transformation& transformation);
	void setRotation(float rotation);
	void setTranslation(float x, float y, float z);
	void setScale(float scale);
	void setRotationSpeed(float speed);

private:
	Model* model;
	ShaderProgram* shaderProgram;
	Transformation transformation;
	float rotationSpeed = 0.0f;
};
