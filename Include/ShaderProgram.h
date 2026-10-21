#pragma once

#include <glad/gl.h>
#include "Shader.h"

#include "ICameraObserver.h"




class ShaderProgram : public ICameraObserver{
public:
	ShaderProgram();
	~ShaderProgram();

	void create(const char* vertexFile, const char* fragmentFile);
	void use();
	void setUniform(const char* name, float value);
	void setUniform(const char* name, float x, float y, float z);

	void setUniform(const char* name, const glm::mat4& matrix);

	void onCameraChanged(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& eye) override;

private:
	GLuint shaderProgram;

	Shader vertexShader;
	Shader fragmentShader;
};
