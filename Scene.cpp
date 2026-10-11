#include "Scene.h"

#include <utility>

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
	drawableObjects.clear();

	shaderPrograms.clear();
	elapsedTime = 0.0;
}

void Scene::update(double deltaTime)
{
	elapsedTime += deltaTime;
}

void Scene::Draw()
{
	for (const auto& object : drawableObjects)
	{
		object->draw(elapsedTime);
	}
}

ShaderProgram* Scene::createShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	auto shader = std::make_unique<ShaderProgram>();
	shader->create(vertexFile, fragmentFile);

	ShaderProgram* result = shader.get();
	shaderPrograms.push_back(std::move(shader));

	return result;
}

DrawableObject* Scene::addObject(Model* model, ShaderProgram* shaderProgram)
{
	auto object = std::make_unique<DrawableObject>(*model, shaderProgram);

	DrawableObject* result = object.get();
	drawableObjects.push_back(std::move(object));

	return result;
}
