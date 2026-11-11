#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION

#include "Application.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>


#include <memory>

#include "Callbacks.h"
#include "Scenes/TransformationScene.hpp"
#include "Scenes/SolarSystemScene.hpp"
#include "Scenes/TriangleScene.hpp"
#include "Scenes/ForestScene.hpp"
#include "Scenes/LightingScene.hpp"
#include "Scenes/CV72aScene.hpp"
#include "Scenes/CV72bScene.hpp"
#include "Scenes/CV72cScene.hpp"
#include "Scenes/CV72dScene.hpp"
#include "Scenes/CV8Scene.hpp"
#include "Scenes/CV8SkydomeScene.hpp"
#include "Scenes/FionaScene.hpp"
#include "Scenes/CV8ModelTestScene.hpp"
#include "Scenes/CV9Scene.hpp"


#include "camera.h"

Application::Application() : window(nullptr)
{
}

Application::~Application()
{
	if (previewWindow)
	{
		glfwMakeContextCurrent(previewWindow);
		glUseProgram(0);
		previewScene.reset();
		glfwDestroyWindow(previewWindow);
		glfwMakeContextCurrent(window);
	}

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
#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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

	int textureUnits;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
	printf("Texture units: %d\n", textureUnits);

	// Sets the key callback
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_callback);

	glfwSetMouseButtonCallback(window, button_callback);

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	//glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetFramebufferSizeCallback(window, window_size_callback);
	glfwSetScrollCallback(window, scroll_callback);

	return true;
}

void Application::drawPreview(const CV9Scene& scene, double time)
{
	if (!previewWindow)
	{
		glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
		previewWindow = glfwCreateWindow(320, 320, "Nahled modelu", nullptr, window);
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
		if (!previewWindow)
			return;

		glfwSetWindowCloseCallback(previewWindow, glfwHideWindow);
		glfwMakeContextCurrent(previewWindow);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
		previewScene = std::make_unique<ModelPreviewScene>();
	}
	else
	{
		if (glfwWindowShouldClose(previewWindow))
			return;

		if (!glfwGetWindowAttrib(previewWindow, GLFW_VISIBLE))
			glfwShowWindow(previewWindow);

		glfwMakeContextCurrent(previewWindow);
	}

	int width, height;
	glfwGetFramebufferSize(previewWindow, &width, &height);
	glViewport(0, 0, width, height);
	previewScene->getCamera()->setPerspective(width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	previewScene->drawModel(scene.getPreviewModel(), time);
	glfwSwapBuffers(previewWindow);

	glfwMakeContextCurrent(window);
}

void Application::run()
{
	// sceneManager.addScene(std::make_unique<TransformationScene>());
	sceneManager.addScene(std::make_unique<SolarSystemScene>());
	sceneManager.addScene(std::make_unique<ForestScene>());
	// sceneManager.addScene(std::make_unique<LightingScene>());
	//sceneManager.addScene(std::make_unique<CV72aScene>());
	//sceneManager.addScene(std::make_unique<CV72bScene>());
	//sceneManager.addScene(std::make_unique<CV72cScene>());
	//sceneManager.addScene(std::make_unique<CV72dScene>());
	// sceneManager.addScene(std::make_unique<CV8Scene>());
	// sceneManager.addScene(std::make_unique<CV8SkydomeScene>());
	// sceneManager.addScene(std::make_unique<FionaScene>());
	// sceneManager.addScene(std::make_unique<CV8ModelTestScene>());
	sceneManager.addScene(std::make_unique<CV9Scene>());
	sceneManager.switchScene(1);

	glfwSetWindowTitle(window, sceneManager.getActiveScene().getName().c_str());

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	//glViewport(0, 0, width, height);
	inputManager.handleResize(width, height);


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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		Scene& scene = sceneManager.getActiveScene();

		inputManager.updateMovement(scene, deltaTime);

		scene.update(deltaTime, static_cast<float>(currentTime));
		scene.Draw();

		inputManager.processClick(scene);

		glfwSwapBuffers(window);

		const auto* cv9 = dynamic_cast<const CV9Scene*>(&scene);
		if (cv9 && scene.wantsPreviewWindow())
		{
			drawPreview(*cv9, currentTime);
		}
		else if (previewWindow)
		{
			glfwHideWindow(previewWindow);
			glfwSetWindowShouldClose(previewWindow, GLFW_FALSE);
		}
	}

}
