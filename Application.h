#pragma once

#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "Model.h"

#include "Scene.h"
#include <vector>
#include <cstddef>

class Application
{
public:
	Application();
	~Application();

	bool initialization();
	//void createShaders();
	//void createModels();
	void run();
	void handleKey(int key, int action);



private:
	GLFWwindow* window;

	//GLuint VBO;
	//GLuint VAO;
	//Model model;
	//ShaderProgram shaderProgram;
	//Model model1;
	//ShaderProgram shaderProgram1;
	
	//ShaderProgram* shaderProgram;
	//ShaderProgram* shaderProgram1;
	std::vector<Scene*> scenes;
	std::size_t activeScene = 0;

	Scene* createScene(const char* name);
	void createScenes();
	void switchScene(std::size_t index);
};
