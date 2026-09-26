#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION

#include "Application.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "Models/gift.h"
#include "Models/sphere.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

#include "Callbacks.h"


Application::Application() : window(nullptr)
{

}

bool Application::initialization()
{

	glfwSetErrorCallback(error_callback);

	// Initialize GLFW
	if (!glfwInit()) {
		//exit(EXIT_FAILURE);
		return false;
	}
		

	//Initialization of a specific version

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //


	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();

		//exit(EXIT_FAILURE);
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Initialize GLAD and load OpenGL function pointers
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		printf("GLAD initialization failed\n");
		return false;
	}

	// Get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	// Sets the key callback
	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_callback);

	glfwSetMouseButtonCallback(window, button_callback);

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);




	return true;
}

void Application::createShaders()
{
	shaderProgram.create("shaders/basic.vert", "shaders/basic.frag");
}

void Application::createModels()
{
	float points[] = {
	 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};

	model.create(sphere, sizeof(sphere));
}

void Application::run()
{
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
	while (!glfwWindowShouldClose(window))
	{
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.use(); //glUseProgram(shaderProgram);
		//glBindVertexArray(VAO);

		//// Draw a triangles
		//glDrawArrays(GL_TRIANGLES, 0, 2880); //mode,first,count

		model.draw(1000);

		// Display the rendered frame and process events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
