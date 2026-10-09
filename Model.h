#pragma once

#include <glad/gl.h>

class Model
{
public:
	Model();
	~Model();

	void create(const float* vertices, int dataSize, int floatsPerVertex = 6);
	void draw();

private:
	GLuint VBO;
	GLuint VAO;
	int vertexCount;
};