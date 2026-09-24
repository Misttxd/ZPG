#pragma once

#include <glad/gl.h>

class Model
{
public:
	Model();

	void create(const float* vertices, int dataSize);
	void draw(int vertexCount);

private:
	GLuint VBO;
	GLuint VAO;
};