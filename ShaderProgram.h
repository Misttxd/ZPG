#pragma once

#include <glad/gl.h>



class ShaderProgram {
public:
	ShaderProgram();

	void create(const char* vertexFile, const char* fragmentFile);
	void use();

	//GLuint getShaderprogramId(); //TODO - tohle není potřeba, předělat to kde se to potřebuje do ShaderProgramu, tim padem bude shaderProgram (gluint promenna) zakapsulovana a real private
	//TODO + práci s shaderprogramem udělat přes přetížené parametry
private:
	GLuint shaderProgram;

	void setUniform(const char* name, float value);
	void setUniform(const char* name, float x, float y, float z);

	GLuint createShaderFromFile(GLenum shaderType, const char* shaderFile);
};
