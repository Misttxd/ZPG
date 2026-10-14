#include <glad/gl.h>
#include "Callbacks.h"
#include "Application.h"

#include <stdio.h>

void error_callback(int error, const char* description) { fputs(description, stderr); }

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app != nullptr)
	{
		app->handleKey(key, action);
	}
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void window_focus_callback(GLFWwindow* window, int focused) 
{ 
	printf("window_focus_callback \n"); 
	Application* app =
		static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (app && !focused)
	{
		app->handleMouseButton(GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE);
	}
}

void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

//void window_size_callback(GLFWwindow* window, int width, int height) {
//	printf("resize %d, %d \n", width, height);
//	glfwGetFramebufferSize(window, &width, &height);
//	glViewport(0, 0, width, height);
//}

void window_size_callback(GLFWwindow* window, int width, int height) //neo
{
	printf("resize %d, %d \n", width, height);

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (app)
	{
		app->handleResize(width, height);
	}
}

//void cursor_callback(GLFWwindow* window, double x, double y) 
// { 
//	printf("cursor_callback \n"); 
// }

void cursor_callback(GLFWwindow* window, double x, double y)
{
	printf("cursor_callback \n");

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (app)
	{
		app->handleMouseMove(x, y);
	}
}

void button_callback(GLFWwindow* window, int button, int action, int mode)
{
    if (action == GLFW_PRESS)
	{
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

    if (app)
    {
        app->handleMouseButton(button, action);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (app)
	{
		app->handleScroll(yoffset);
	}
}