#include "Scene/Scene.h"
#include "DrawableObject.h"

#include "camera.h"

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
	if (camera)
	{
		camera->clearObservers();
	}

	lights.clear();
	drawableObjects.clear();

	shaderPrograms.clear();
	elapsedTime = 0.0;
}


void Scene::update(double deltaTime, float clockTime)
{
	elapsedTime += deltaTime;
}

void Scene::Draw()
{
    for (const auto& program : shaderPrograms)
        program->setLights(lights);

	for (const auto& object : drawableObjects)
	{
		object->draw(elapsedTime);
	}
}

ShaderProgram& Scene::addShaderProgram(const char* vertexShader, const char* fragmentShader, bool usesCamera)
{
	auto shader = std::make_unique<ShaderProgram>();
	shader->create(vertexShader, fragmentShader);

	shaderPrograms.push_back(std::move(shader));

	if (camera && usesCamera)
	{
		camera->addObserver(*shaderPrograms.back());
	}

	return *shaderPrograms.back();
}

DrawableObject& Scene::addObject(std::unique_ptr<DrawableObject> object)
{
	if (!object) throw std::invalid_argument("Scene must not contain a null object.");

	drawableObjects.push_back(std::move(object));
    return *drawableObjects.back();
}


Camera& Scene::createCamera()
{
	camera = std::make_unique<Camera>();
	return *camera;
}

Camera* Scene::getCamera()
{
	return camera.get();
}

Light& Scene::addLight(const Light& light)
{
    if (lights.size() >= MaxLights)
        throw std::runtime_error("Scene supports at most 8 lights.");
    lights.push_back(std::make_unique<Light>(light));
    return *lights.back();
}

void Scene::removeLight(const Light& light)
{
    for (auto it = lights.begin(); it != lights.end(); ++it)
    {
        if (it->get() == &light)
        {
            lights.erase(it);
            return;
        }
    }
}
