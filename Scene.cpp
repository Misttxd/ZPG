#include "Scene.h"

Scene::Scene(const char* name) : name(name)
{
}

const std::string& Scene::getName() const
{
	return name;
}

Scene::~Scene()
{
	clear();
}

void Scene::clear()
{
	for (DrawableObject* object : drawableObjects)
	{
		delete object;
	}
	drawableObjects.clear();

	for (ShaderProgram* shaderProgram : shaderPrograms)
	{
		delete shaderProgram;
	}
	shaderPrograms.clear();

	for (Model* model : models)
	{
		delete model;
	}
	models.clear();
}

void Scene::Draw()
{
	for (DrawableObject* object : drawableObjects)
	{
		object->draw();
	}
}

Model* Scene::createModel(const float* vertices, int dataSize, int floatsPerVertex)
{
	Model* model = new Model();
	model->create(vertices, dataSize, floatsPerVertex);
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

DrawableObject* Scene::addObject(Model* model, ShaderProgram* shaderProgram, const Transformation& transformation)
{
	DrawableObject* drawableObject = new DrawableObject(model, shaderProgram);
	drawableObject->setTransformation(transformation);

	drawableObjects.push_back(drawableObject);

	return drawableObject;
}


void Scene::update(float deltaTime)
{
	for (DrawableObject* object : drawableObjects)
	{
		object->update(deltaTime);
	}
}
