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

#include "Callbacks.h"
#include "Models/BRU0098.h"
#include "Models/sphere.h"
#include "Models/tree.h"
#include "Models/bushes.h"



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

		//exit(EXIT_FAILURE);
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Initialize GLAD and load OpenGL function pointers
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





	//Scena 1
	Scene* triangleScene = createScene("Trojuhelnik");
	ShaderProgram* triangleProgram = triangleScene->createShaderProgram(vertexFile, normalFile);

	float points[] = {
		 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};
	Model* triangleModel = triangleScene->createModel(points, sizeof(points));

	Model* loginModelB1 = triangleScene->createModel(bru0098, sizeof(bru0098));

	Transformation trianglePlacement;
	DrawableObject* triangleObject = triangleScene->addObject(triangleModel, triangleProgram, Transformation());
	triangleObject->setRotationSpeed(0.0f);

	DrawableObject* loginObjectB1 = triangleScene->addObject(loginModelB1, triangleProgram, Transformation());
	loginObjectB1->setTranslation(0.6f, -0.8f, 0.0f);
	loginObjectB1->setScale(0.09);


	//Scena 2 
	Scene* sphereScene = createScene("Sphere scene");
	ShaderProgram* sphereProgram = sphereScene->createShaderProgram(vertexFile, normalFile);
	Model* sphereModel = sphereScene->createModel(sphere, sizeof(sphere));
	
	Model* loginModelB = sphereScene->createModel(bru0098, sizeof(bru0098)); 

	Transformation spherePlacement;
	spherePlacement.setTranslation(0.0f, 0.0f, 0.0f);
	spherePlacement.setScale(0.25f);
	spherePlacement.setRotation(0.5f);
	DrawableObject* sphereObject = sphereScene->addObject(sphereModel, sphereProgram, spherePlacement);

	DrawableObject* loginObjectB = sphereScene->addObject(loginModelB, sphereProgram, Transformation());
	loginObjectB->setTranslation(0.6f, -0.8f, 0.0f);
	loginObjectB->setScale(0.09);
	sphereObject->setRotationSpeed(0.3f);


	//Scena 3
	Scene* forestScene = createScene("forest scene");
	ShaderProgram* forestProgram = forestScene->createShaderProgram(vertexFile, normalFile);
	Model* loginModelB3 = triangleScene->createModel(bru0098, sizeof(bru0098));
	Model* treeModel = forestScene->createModel(tree, sizeof(tree));
	Model* bushModel = forestScene->createModel(bushes, sizeof(bushes));


	for (int row = 0; row < 1; row++)
	{
		for (int column = 0; column < 11; column++)
		{
			DrawableObject* treeObject = forestScene->addObject(treeModel, forestProgram, Transformation());

			float x = -0.9f + column * 0.18f;
			float y = -0.8f + row * 0.5f;

			treeObject->setTranslation(x, y, 0.0f);
			treeObject->setScale(0.045f);
		}
	}

	for (int row = 1; row < 2; row++)
	{
		for (int column = 0; column < 11; column++)
		{
			DrawableObject* bushObject = forestScene->addObject(bushModel, forestProgram, Transformation());

			float x = -0.9f + column * 0.17f;
			float y = -0.8f + row * 0.5f;

			bushObject->setTranslation(x, y, 0.0f);
			bushObject->setScale(0.5f);
		}
	}
	ShaderProgram* sunProgram = sphereScene->createShaderProgram(vertexFile, colorFile);
	DrawableObject* sphereObject2 = forestScene->addObject(sphereModel, sunProgram, Transformation());
	sphereObject2->setTranslation(0.8f, 0.8f, 0.0f);
	sphereObject2->setScale(0.2f);

	DrawableObject* loginObjectB3 = forestScene->addObject(loginModelB3, forestProgram, Transformation());
	loginObjectB3->setTranslation(0.6f, -0.8f, 0.0f);
	loginObjectB3->setScale(0.09);
	




	//Scena 4
	Scene* loginScene = createScene("Login BRU0098");
	ShaderProgram* loginProgram = loginScene->createShaderProgram(vertexFile, normalFile);
	Model* loginModel = loginScene->createModel(bru0098, sizeof(bru0098));

	Transformation loginPlacement;
	loginPlacement.setTranslation(0.0f, 0.0f, 0.0f);
	loginPlacement.setScale(0.25f);
	loginPlacement.setRotation(0.5f);
	DrawableObject* loginObject = loginScene->addObject(loginModel, loginProgram, loginPlacement);
	loginObject->setRotationSpeed(0.3f); 

	switchScene(0);
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
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.

	double previousTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwWindowShouldClose(window))
		{
			break;
		}

		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - previousTime);
		previousTime = currentTime;

		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!scenes.empty())
		{
			scenes[activeScene]->update(deltaTime);
			scenes[activeScene]->Draw();
		}

		// Display the rendered frame
		glfwSwapBuffers(window);
	}
	// Sceny a potom okno uvolni destruktor Application.
}
