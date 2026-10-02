#pragma once
#include "ShaderProgram.h"

class Transformation
{
public:
	Transformation();
	
	void setTranslation(float x, float y, float z);
	void setScale(float scale);
	void setRotation(float rotation);

	void apply(ShaderProgram* shaderProgram);

private:
	float translationX;
	float translationY;
	float translationZ;
	float scale;
	float rotation;
};
