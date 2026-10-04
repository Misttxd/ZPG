#include "Scene.h"

#include "Models/BRU0098.h"

Scene::Scene() : animatedObject(nullptr)
{
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

	animatedObject = nullptr;

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

void Scene::initialization()
{
	ShaderProgram* shaderProgram = createShaders();
	animatedObject = createModels(shaderProgram);
}

void Scene::update(float time)
{
	if (animatedObject != nullptr)
	{
		animatedObject->setRotation(0.5f + time * 0.3f);
	}
}

ShaderProgram* Scene::createShaders()
{
	return createShaderProgram("shaders/right.vert", "shaders/right.frag");
}

DrawableObject* Scene::createModels(ShaderProgram* shaderProgram)
{
	Model* BRU0098Model = createModel(bru0098, sizeof(bru0098));
	DrawableObject* object = createDrawableObject(BRU0098Model, shaderProgram);

	Transformation transformation;
	transformation.setTranslation(0.0f, 0.0f, 0.0f);
	transformation.setScale(0.25f);
	transformation.setRotation(0.5f);

	object->setTransformation(transformation);
	return object;
}