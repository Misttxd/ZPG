#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION

#include "../Include/Application.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>


#include <memory>

#include "../Include/Callbacks.h"
#include "../Include/TransformationScene.hpp"
#include "../Include/SolarSystemScene.hpp"
#include "../Include/TriangleScene.hpp"

Application::Application() : window(nullptr)
{
}

Application::~Application()
{
	if (window != nullptr)
	{
		glUseProgram(0);
	}

	sceneManager.clear();

	if (window != nullptr)
	{
		glfwDestroyWindow(window);
		window = nullptr;
		glfwTerminate();
	}
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

		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		printf("GLAD initialization failed\n");
		glfwDestroyWindow(window);
		window = nullptr;
		glfwTerminate();
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
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_callback);

	glfwSetMouseButtonCallback(window, button_callback);

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);

	return true;
}

void Application::handleKey(int key, int action)
{
    if (sceneManager.handleKey(key, action))
    {
        glfwSetWindowTitle(window, sceneManager.getActiveScene().getName().c_str());
    }
}

void Application::run()
{
	sceneManager.addScene(std::make_unique<TransformationScene>());
	sceneManager.addScene(std::make_unique<SolarSystemScene>());
	sceneManager.addScene(std::make_unique<TriangleScene>());
	sceneManager.switchScene(1);

	glfwSetWindowTitle(window, sceneManager.getActiveScene().getName().c_str());

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	// A square viewport preserves proportions without a projection matrix.
	int viewportSize = width < height ? width : height;
	glViewport((width - viewportSize) / 2, (height - viewportSize) / 2, viewportSize, viewportSize);

	glEnable(GL_DEPTH_TEST);

	double previousTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwWindowShouldClose(window))
		{
			break;
		}

		double currentTime = glfwGetTime();
		double deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Scene& scene = sceneManager.getActiveScene();
		scene.update(deltaTime);
		scene.Draw();


		glfwSwapBuffers(window);
	}

}
