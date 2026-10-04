#pragma once
#include <vector>

//#include <memory> //hodilo by se to pak předělat na tohle jeslti bude delat problem delete

#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"

using std::vector;
class Scene
{
public:
	Scene();
	~Scene();
	void Draw();
	Model* createModel(const float* vertices, int dataSize);
	ShaderProgram* createShaderProgram(const char* vertexFile, const char* fragmentFile);
	DrawableObject* createDrawableObject(Model* model, ShaderProgram* shaderProgram);
	void initialization();
	void update(float time);
	void clear();

private:
	vector<Model*>models;
	vector<ShaderProgram*>shaderPrograms;
	vector<DrawableObject*>drawableObjects;	
	ShaderProgram* createShaders();
	DrawableObject* createModels(ShaderProgram* shaderProgram);
	DrawableObject* animatedObject;
};

