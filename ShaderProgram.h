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

private:
	GLint getUniformLocation(const char* name) const;

	GLuint shaderProgram;

	Shader vertexShader;
	Shader fragmentShader;
};
