#pragma once
#include <vector>
#include <string>
#include <memory>

#include "ShaderProgram.h"
class DrawableObject;

using std::vector;
class Scene
{
public:
	Scene(const char* name);
	virtual ~Scene();
	const std::string& getName() const;
	void Draw();
	void update(double deltaTime);
	ShaderProgram& addShaderProgram(const char* vertexShader, const char* fragmentShader);
	DrawableObject& addObject(std::unique_ptr<DrawableObject> object);
	void clear();

private:
	std::string name;
	double elapsedTime = 0.0;
	vector<std::unique_ptr<ShaderProgram>> shaderPrograms;
	vector<std::unique_ptr<DrawableObject>> drawableObjects;
};

