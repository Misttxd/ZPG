#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION

#include "Application.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>


#include <memory>

#include "Callbacks.h"
#include "TransformationScene.hpp"
#include "SolarSystemScene.hpp"
#include "TriangleScene.hpp"
#include "ForestScene.hpp"


#include "camera.h" //neo

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

	//glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetFramebufferSizeCallback(window, window_size_callback); //neo
	glfwSetScrollCallback(window, scroll_callback);

	return true;
}

void Application::handleKey(int key, int action)
{
    if (sceneManager.handleKey(key, action))
    {
        glfwSetWindowTitle(window, sceneManager.getActiveScene().getName().c_str());
		
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		handleResize(width, height);
		mouseDragging = false;
    }
}

void Application::run()
{
	sceneManager.addScene(std::make_unique<TransformationScene>());
	sceneManager.addScene(std::make_unique<SolarSystemScene>());
	sceneManager.addScene(std::make_unique<TriangleScene>());
	sceneManager.addScene(std::make_unique<TriangleScene>(false));
	sceneManager.addScene(std::make_unique<ForestScene>());
	sceneManager.switchScene(1);

	glfwSetWindowTitle(window, sceneManager.getActiveScene().getName().c_str());

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	//glViewport(0, 0, width, height);
	handleResize(width, height);

	double clockTime = glfwGetTime();

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

		Camera* camera = scene.getCamera();

		if (camera && glfwGetWindowAttrib(window, GLFW_FOCUSED))
		{
			float forward = 0.0f;
			float sideways = 0.0f;
			float vertical = 0.0f;


			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) forward += 1.0f;
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) forward -= 1.0f;

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) sideways += 1.0f;
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) sideways -= 1.0f;

			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) vertical -= 1.0f;
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) vertical += 1.0f;

			//if (glfwGetKey(window, scroll) == GLFW_PRESS) camera->speed += 1.0;



			camera->move(forward, sideways, vertical, deltaTime);
		}
		
		scene.update(deltaTime,(float) clockTime);
		scene.Draw();


		glfwSwapBuffers(window);
	}

}

void Application::handleResize(int width, int height)
{
	glViewport(0, 0, width, height);

	Camera* camera = sceneManager.getActiveScene().getCamera();
	if (camera)
	{
		camera->setPerspective(width, height);
	}
}

void Application::handleScroll(double yoffset)
{
	Camera* camera = sceneManager.getActiveScene().getCamera();

	if (!camera)
	{
		return;
	}

	camera->speed += static_cast<float>(yoffset);

	if (camera->speed < 0.1f)
	{
		camera->speed = 0.1f;
	}
}


void Application::handleMouseButton(int button, int action)
{
	if (button != GLFW_MOUSE_BUTTON_RIGHT)
	{
		return;
	}

	mouseDragging = action == GLFW_PRESS;

	if (mouseDragging)
	{
		glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
	}
}

void Application::handleMouseMove(double x, double y)
{
	if (!mouseDragging || !glfwGetWindowAttrib(window, GLFW_FOCUSED))
	{
		return;
	}

	double deltaX = x - lastMouseX;
	double deltaY = y - lastMouseY;

	lastMouseX = x;
	lastMouseY = y;

	Camera* camera = sceneManager.getActiveScene().getCamera();

	if (camera)
	{
		camera->rotate(static_cast<float>(deltaX), static_cast<float>(deltaY));
	}
}

