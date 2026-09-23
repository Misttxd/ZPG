#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Application
{
public:
	Application();

	bool Initialization();
	void createShaders();
	void createModels();
	void run();



private:
	GLFWwindow* window;
};
