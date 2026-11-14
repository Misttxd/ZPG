#include <glad/gl.h>
#include "Callbacks.h"
#include "Application.h"

#include <stdio.h>

namespace{

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app != nullptr)
	{
		app->getInputManager().handleKey(key, action);
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
		app->getInputManager().handleMouseButton(GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE);
	}
}

void window_iconify_callback(GLFWwindow* window, int iconified) { 
	printf("window_iconify_callback \n"); 
}

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
		app->getInputManager().handleResize(width, height);
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
		app->getInputManager().handleMouseMove(x, y);
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
        app->getInputManager().handleMouseButton(button, action);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (app)
	{
		app->getInputManager().handleScroll(yoffset);
	}
}

}//namespace



void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void registerCallbacks(GLFWwindow* window, void* pointer)
{
	// Get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int textureUnits;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
	printf("Texture units: %d\n", textureUnits);


	glfwSetWindowUserPointer(window, pointer);
	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_callback);

	glfwSetMouseButtonCallback(window, button_callback);

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	//glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetFramebufferSizeCallback(window, window_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
}
