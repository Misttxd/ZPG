#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (DrawableObject* object : drawableObjects)
	{
		delete object;
	}

	for (ShaderProgram* shaderProgram : shaderPrograms)
	{
		delete shaderProgram;
	}

	for (Model* model : models)
	{
		delete model;
	}
}

void Scene::Draw()
{
	for (DrawableObject* object : drawableObjects)
	{
		object->draw();
	}
}