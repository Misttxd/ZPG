#pragma once


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "InputManager.h"

class CV9Scene;
class ModelPreviewScene;

class Application
{
public:
	Application();
	~Application();

	bool initialization();

	void run();
	InputManager& getInputManager() { return inputManager; }

private:
	GLFWwindow* window;
	SceneManager sceneManager;
	InputManager inputManager{window, sceneManager};

	GLFWwindow* previewWindow = nullptr;
	std::unique_ptr<ModelPreviewScene> previewScene;

	void drawPreview(const CV9Scene& scene, double time);
};
