#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"

using std::vector;
class Scene
{
public:
	Scene(const char* name);
	~Scene();
	const std::string& getName() const;
	void Draw();
	void update(double deltaTime);
	ShaderProgram* createShaderProgram(const char* vertexFile, const char* fragmentFile);
	DrawableObject* addObject(Model* model, ShaderProgram* shaderProgram);
	void clear();

private:
	std::string name;
	double elapsedTime = 0.0;
	vector<std::unique_ptr<ShaderProgram>> shaderPrograms;
	vector<std::unique_ptr<DrawableObject>> drawableObjects;
};

