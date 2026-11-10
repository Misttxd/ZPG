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
	virtual void Draw();
	virtual void update(double deltaTime, float clockTime);
	virtual void onWorldClick(GLuint index, const glm::vec3& pos) {}
	virtual void onKeyPressed(int) {}


	ShaderProgram& addShaderProgram(const char* vertexShader, const char* fragmentShader, bool usesCamera = true);


	DrawableObject& addObject(std::unique_ptr<DrawableObject> object);
	void clear();

    static constexpr int MaxLights = 8; //eq to max lights
    Light& addLight(const Light& light = Light());
    void removeLight(const Light& light);

	void readClickedPixel(GLint x, GLint y, int width, int height);

	Camera* getCamera();


	virtual bool wantsPreviewWindow() const 
	{ 
		return false; 
	}

private:
	std::string name;
	std::unique_ptr<Camera> camera;
	vector<std::unique_ptr<ShaderProgram>> shaderPrograms;
	vector<std::unique_ptr<DrawableObject>> drawableObjects;

	int idCounter;



protected:
	std::vector<std::unique_ptr<Light>> lights;
	double elapsedTime = 0.0;
	DrawableObject* findObject(GLuint id);
	Camera& createCamera();
};

