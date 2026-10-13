#pragma once
#include <vector>
#include <string>
#include <memory>

#include "ShaderProgram.h"
class DrawableObject;

class Camera;

using std::vector;
class Scene
{
public:
	Scene(const char* name);
	virtual ~Scene();
	const std::string& getName() const;
	void Draw();
	void update(double deltaTime);


	ShaderProgram& addShaderProgram(const char* vertexShader, const char* fragmentShader, bool usesCamera = true);


	DrawableObject& addObject(std::unique_ptr<DrawableObject> object);
	void clear();

	Camera* getCamera();

private:
	std::string name;
	double elapsedTime = 0.0;
	std::unique_ptr<Camera> camera;
	vector<std::unique_ptr<ShaderProgram>> shaderPrograms;
	vector<std::unique_ptr<DrawableObject>> drawableObjects;

protected:
	Camera& createCamera();
};

