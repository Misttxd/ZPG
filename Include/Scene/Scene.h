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
	virtual void update(double deltaTime, float clockTime);


	ShaderProgram& addShaderProgram(const char* vertexShader, const char* fragmentShader, bool usesCamera = true);


	DrawableObject& addObject(std::unique_ptr<DrawableObject> object);
	void clear();
    // Keep this equal to MAX_LIGHTS in the lighting fragment shaders.
    static constexpr int MaxLights = 8;
    Light& addLight(const Light& light = Light());
    void removeLight(const Light& light);

	Camera* getCamera();
private:
	std::vector<std::unique_ptr<Light>> lights;
	std::string name;
	double elapsedTime = 0.0;
	std::unique_ptr<Camera> camera;
	vector<std::unique_ptr<ShaderProgram>> shaderPrograms;
	vector<std::unique_ptr<DrawableObject>> drawableObjects;



protected:
	Camera& createCamera();
};

