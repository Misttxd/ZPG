#include "../Include/Scenes/Scene.h"
#include "../Include/Objects/DrawableObject.h"

#include <utility>
#include <stdexcept>

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

ShaderProgram& Scene::addShaderProgram(const char* vertexShader, const char* fragmentShader)
{
	auto shader = std::make_unique<ShaderProgram>();
	shader->create(vertexShader, fragmentShader);

	shaderPrograms.push_back(std::move(shader));
	return *shaderPrograms.back();
}

DrawableObject& Scene::addObject(std::unique_ptr<DrawableObject> object)
{
	if (!object)
		throw std::invalid_argument("Scene must not contain a null object.");

	drawableObjects.push_back(std::move(object));
    return *drawableObjects.back();
}
