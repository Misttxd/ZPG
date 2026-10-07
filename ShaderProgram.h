#pragma once

#include <glad/gl.h>
#include "Shader.h"

#include <glm/glm.hpp>



class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	void create(const char* vertexFile, const char* fragmentFile);
	void use();
	void setUniform(const char* name, float value);
	void setUniform(const char* name, float x, float y, float z);

	void setUniform(const char* name, const glm::mat4& matrix);

	//GLuint getShaderprogramId(); //TODO - tohle není potřeba, předělat to kde se to potřebuje do ShaderProgramu, tim padem bude shaderProgram (gluint promenna) zakapsulovana a real private
	//TODO + práci s shaderprogramem udělat přes přetížené parametry
private:
	GLuint shaderProgram;

	Shader vertexShader;
	Shader fragmentShader;
};
