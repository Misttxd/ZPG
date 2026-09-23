#pragma once

#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Application
{
public:
	Application();

	bool initialization();
	void createShaders();
	void createModels();
	void run();



private:
	GLFWwindow* window;

	GLuint VBO;
	GLuint VAO;
	GLuint shaderProgram;
};
