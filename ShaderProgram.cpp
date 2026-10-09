#include "ShaderProgram.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram() : shaderProgram(0) {

}
ShaderProgram::~ShaderProgram()
{
	if (shaderProgram != 0)
	{
		glDeleteProgram(shaderProgram);
	}
}

void ShaderProgram::create(const char* vertexFile, const char* fragmentFile)
{
	vertexShader.createShaderFromFile(GL_VERTEX_SHADER, vertexFile);
	fragmentShader.createShaderFromFile(GL_FRAGMENT_SHADER, fragmentFile);

	shaderProgram = glCreateProgram();

	fragmentShader.attachTo(shaderProgram);
	vertexShader.attachTo(shaderProgram);

	glLinkProgram(shaderProgram);
}

void ShaderProgram::use()
{
	glUseProgram(shaderProgram);
}


void ShaderProgram::setUniform(const char* name, float value)
{
	use();

	int location = glGetUniformLocation(shaderProgram, name);
	if (location != -1)
	{
		glUniform1f(location, value);
	}
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z) 
{
	use();

	int location = glGetUniformLocation(shaderProgram, name);
	if (location != -1) {
		glUniform3f(location, x, y, z);
	}
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& matrix)
{
	use();

	GLint location = glGetUniformLocation(shaderProgram, name);
	if (location != -1)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

	}
}