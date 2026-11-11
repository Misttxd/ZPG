#include "Scene.h"
#include "DrawableObject.h"

#include "camera.h"

#include <glm/ext/matrix_projection.hpp>
#include <cstdio>
#include <utility>
#include <stdexcept>

Scene::Scene(const char* name) : name(name), idCounter(1)
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
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


    for (const auto& program : shaderPrograms)
        program->setLights(lights);

	for (const auto& object : drawableObjects)
	{
		glStencilFunc(GL_ALWAYS, object->getId(), 0xFF);
		object->draw(elapsedTime);
	}
}


void Scene::readClickedPixel(GLint x, GLint y, int width, int height)
{
	int newY = height - 1 - y;
	if (x < 0 || x >= width || newY < 0 || newY >= height) {
		return;
	}

	GLubyte color[4]{};
	GLfloat depth = 1.0f;
	GLuint index = 0;
	glReadPixels(x, newY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	std::printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
		x, y, color[0], color[1], color[2], color[3], depth, index);

	if (camera && depth < 1.0f)
	{
		glm::vec3 screenPoint(x, newY, depth);
		const glm::mat4& view = camera->getViewMatrix();
		const glm::mat4& projection = camera->getProjectionMatrix();
		glm::vec4 viewport(0, 0, width, height);
		glm::vec3 pos = glm::unProject(screenPoint, view, projection, viewport);

		onWorldClick(index, pos);

		std::printf("unProject [%f, %f, %f]\n", pos.x, pos.y, pos.z);
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

	object->setId(idCounter);

	drawableObjects.push_back(std::move(object));
	idCounter++;
    return *drawableObjects.back();
}


DrawableObject* Scene::findObject(GLuint id) const {
	for (const auto& object : drawableObjects)
	{
		if (static_cast<GLuint>(object->getId()) == id)
			return object.get();
	}
	return nullptr;
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

