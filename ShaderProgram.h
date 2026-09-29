#pragma once

#include <glad/gl.h>



class ShaderProgram {
public:
	ShaderProgram();

	void create(const char* vertexFile, const char* fragmentFile);
	void use();

	GLuint getShaderprogramId();

private:
	GLuint shaderProgram;

	GLuint createShaderFromFile(GLenum shaderType, const char* shaderFile);
};
