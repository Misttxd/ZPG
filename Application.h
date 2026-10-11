#pragma once

#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "Model.h"

#include "Scene.h"
#include <vector>
#include <cstddef>
#include <memory>

class Application
{
public:
	Application();
	~Application();

	bool initialization();

	void run();
	void handleKey(int key, int action);



private:
	GLFWwindow* window;

	std::vector<Scene*> scenes;
	std::unique_ptr<Model> sphereModel;
	std::unique_ptr<Model> sunModel;
	std::unique_ptr<Model> earthModel;
	std::unique_ptr<Model> moonModel;
	std::size_t activeScene = 0;

	Scene* createScene(const char* name);
	void createScenes();
	void switchScene(std::size_t index);
};
