#include "ShaderProgram.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>






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

	//GLint success;
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	//if (!success)
	//{
	//	char infoLog[1024];
	//	glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);

	//	std::cout
	//		<< "Program linking failed:\n"
	//		<< infoLog << std::endl;

	//	exit(EXIT_FAILURE);
	//}
}

void ShaderProgram::use()
{
	glUseProgram(shaderProgram);
}

//GLuint ShaderProgram::getShaderprogramId()
//{
//	return this->shaderProgram;
//}

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