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

	void handleResize(int width, int height); //neo
	void handleScroll(double yoffset); //neo

	void handleMouseButton(int button, int action); //neo
	void handleMouseMove(double x, double y); //neo



private:
	GLFWwindow* window;

	SceneManager sceneManager;

	bool mouseDragging = false;
	double lastMouseX = 0.0;
	double lastMouseY = 0.0;
};
