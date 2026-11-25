#pragma once

#include <glad/gl.h>

class Model
{
public:
	Model();
	~Model();
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

	void create(const float* vertices, int dataSize, int floatsPerVertex = 6);
	void draw();

private:
	GLuint VBO;
	GLuint VAO;
	int vertexCount;
};
