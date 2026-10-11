#pragma once


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "SceneManager.hpp"

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

	SceneManager sceneManager;
};
