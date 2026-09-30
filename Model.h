#pragma once

#include <glad/gl.h>

class Model
{
public:
	Model();

	void create(const float* vertices, int dataSize);
	void draw();

private:
	GLuint VBO;
	GLuint VAO;
	int vertexCount;
};