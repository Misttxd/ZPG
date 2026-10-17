#include "Shader.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

Shader::Shader() : shaderID(0)
{
}

Shader::~Shader()
{
	if (shaderID != 0)
	{
		glDeleteShader(shaderID);
	}
}

void Shader::attachTo(GLuint programId)
{
    glAttachShader(programId, shaderID);
}   

void Shader::createShaderFromFile(GLenum shaderType, const char* shaderFile)
{
	shaderID = glCreateShader(shaderType);

	if (shaderID == 0)
	{
		std::cout << "Unable to create shader" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::ifstream file(shaderFile);
	if (!file.is_open())
	{
		std::cout << "Unable to open file " << shaderFile << std::endl;
		glDeleteShader(shaderID);
		exit(-1);
	}
	std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	const char* source = shaderCode.c_str();
	glShaderSource(shaderID, 1, &source, nullptr);

	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
		std::cout
			<< "Shader failed:\n"
			<< infoLog << std::endl;
		glDeleteShader(shaderID);
		exit(1);
	}
}
