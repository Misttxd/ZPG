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

Model* Scene::createModel(const float*vertices , int dataSize)
{
	Model* model = new Model();
	model->create(vertices, dataSize);
	models.push_back(model);
	return model;	
}

ShaderProgram* Scene::createShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	ShaderProgram* shaderProgram = new ShaderProgram();
	shaderProgram->create(vertexFile, fragmentFile);
	shaderPrograms.push_back(shaderProgram);
	return shaderProgram;
}

DrawableObject* Scene::createDrawableObject(Model* model, ShaderProgram* shaderProgram)
{
	DrawableObject* drawableObject = new DrawableObject(model, shaderProgram);

	drawableObjects.push_back(drawableObject);

	return drawableObject;
}