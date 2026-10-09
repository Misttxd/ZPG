#pragma once
#include <vector>
#include <string>

//#include <memory> //hodilo by se to pak předělat na tohle jeslti bude delat problem delete

#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"

using std::vector;
class Scene
{
public:
	Scene(const char* name);
	~Scene();
	const std::string& getName() const;
	void Draw();
	Model* createModel(const float* vertices, int dataSize, int floatsPerVertex = 6);
	ShaderProgram* createShaderProgram(const char* vertexFile, const char* fragmentFile);
	DrawableObject* addObject(Model* model, ShaderProgram* shaderProgram, const Transformation& transformation);
	void update(float deltaTime);
	void clear();

private:
	std::string name;
	vector<Model*>models;
	vector<ShaderProgram*>shaderPrograms;
	vector<DrawableObject*>drawableObjects;	
};

