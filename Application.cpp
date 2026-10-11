#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION

#include "Application.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>


#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <utility>

#include "Callbacks.h"
#include "Models/BRU0098.h"
#include "Models/sphere.h"
#include "Models/tree.h"
#include "Models/bushes.h"

#include "Models/sun.h"
#include "Models/earth.h"
#include "Models/moon.h"



Application::Application() : window(nullptr)
{
}

Application::~Application()
{
	if (window != nullptr)
	{
		glUseProgram(0);
	}

	for (Scene* scene : scenes)
	{
		delete scene;
	}
	scenes.clear();
	sphereModel.reset();
	sunModel.reset();
	earthModel.reset();
	moonModel.reset();

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

Scene* Application::createScene(const char* name)
{
	Scene* scene = new Scene(name);
	scenes.push_back(scene);
	return scene;
}

void Application::createScenes()
{
	const char* vertexFile = "shaders/right.vert";
	const char* colorFile = "shaders/basic.frag";
	const char* normalFile = "shaders/right.frag";

	Scene* scene = createScene("Ukazka transformaci");
	ShaderProgram* normalProgram = scene->createShaderProgram(vertexFile, normalFile);
	ShaderProgram* yellowProgram = scene->createShaderProgram(vertexFile, colorFile);

	sphereModel = std::make_unique<Model>();
	sphereModel->create(sphere, sizeof(sphere));

	DrawableObject* leftSphere = scene->addObject(sphereModel.get(), normalProgram);
	leftSphere->transformation.translate(-0.55f, -0.25f, 0.0f);
	leftSphere->transformation.rotate(30.0f, 0.0f, 1.0f, 0.0f, 30.0f);
	leftSphere->transformation.scale(0.25f, 0.25f, 0.25f);

	DrawableObject* rightSphere = scene->addObject(sphereModel.get(), normalProgram);
	rightSphere->transformation.translate(0.45f, -0.25f, 0.0f);

	Transformation shape;
	shape.rotate(35.0f, 0.0f, 0.0f, 1.0f, -20.0f);
	shape.scale(0.35f, 0.18f, 0.25f);
	rightSphere->transformation.add(std::move(shape));

	DrawableObject* sunObject = scene->addObject(sphereModel.get(), yellowProgram);
	sunObject->transformation.translate(0.0f, 0.5f, 0.0f);
	sunObject->transformation.scale(0.18f, 0.18f, 0.18f);

	Scene* solarScene = createScene("Solar system");
	ShaderProgram* planetProgram = solarScene->createShaderProgram(vertexFile, normalFile);

	sunModel = std::make_unique<Model>();
	sunModel->create(sun, sizeof(sun), 9);
	earthModel = std::make_unique<Model>();
	earthModel->create(earth, sizeof(earth), 9);
	moonModel = std::make_unique<Model>();
	moonModel->create(moon, sizeof(moon), 9);

	const float earthOrbitRadius = 0.56f;
	const float earthOrbitSpeed = 20.0f;
	const float earthOrbitAngle = 25.0f;
	const float moonOrbitRadius = 0.17f;
	const float moonOrbitSpeed = 65.0f;
	const float orbitTilt = 30.0f;

	DrawableObject* solarSun = solarScene->addObject(sunModel.get(), planetProgram);
	solarSun->transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, 12.0f);
	solarSun->transformation.scale(0.19f);

	Transformation earthOrbit;
	earthOrbit.rotate(earthOrbitAngle, 0.0f, 0.0f, 1.0f, earthOrbitSpeed);
	earthOrbit.translate(earthOrbitRadius, 0.0f, 0.0f);

	DrawableObject* earthObject = solarScene->addObject(earthModel.get(), planetProgram);
	earthObject->transformation.rotate(orbitTilt, 1.0f, 0.0f, 0.0f);
	earthObject->transformation.add(std::move(earthOrbit));
	
	
	earthObject->transformation.rotate(23.5f, 0.0f, 0.0f, 1.0f);
	earthObject->transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, 80.0f);
	earthObject->transformation.scale(0.10f);

	Transformation moonEarthOrbit;
	moonEarthOrbit.rotate(earthOrbitAngle, 0.0f, 0.0f, 1.0f, earthOrbitSpeed);
	moonEarthOrbit.translate(earthOrbitRadius, 0.0f, 0.0f);

	Transformation moonOrbit;
	moonOrbit.rotate(110.0f, 0.0f, 0.0f, 1.0f, moonOrbitSpeed);
	moonOrbit.translate(moonOrbitRadius, 0.0f, 0.0f);
	moonEarthOrbit.add(std::move(moonOrbit));

	DrawableObject* moonObject = solarScene->addObject(moonModel.get(), planetProgram);
	moonObject->transformation.rotate(orbitTilt, 1.0f, 0.0f, 0.0f);
	moonObject->transformation.add(std::move(moonEarthOrbit));
	moonObject->transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, 15.0f);
	moonObject->transformation.scale(0.045f);

	switchScene(1);
}

void Application::switchScene(std::size_t index)
{
	if (index < scenes.size())
	{
		activeScene = index;
		glfwSetWindowTitle(window, scenes[activeScene]->getName().c_str());
	}
}

void Application::handleKey(int key, int action)
{
	if (action != GLFW_PRESS || scenes.empty())
	{
		return;
	}

	if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
	{
		switchScene(static_cast<std::size_t>(key - GLFW_KEY_1));
	}
	else if (key == GLFW_KEY_TAB)
	{
		switchScene((activeScene + 1) % scenes.size());
	}
}

void Application::run()
{
	createScenes();

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

		if (!scenes.empty())
		{
			scenes[activeScene]->update(deltaTime);
			scenes[activeScene]->Draw();
		}


		glfwSwapBuffers(window);
	}

}
