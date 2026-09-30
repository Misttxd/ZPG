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

private:
	vector<Model*>models;
	vector<ShaderProgram*>shaderPrograms;
	vector<DrawableObject*>drawableObjects;	
};

