#include "ShaderProgram.h"

#include <stdlib.h>
#include <iostream>
#include <string>

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
    GLint linked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        char log[1024];
        glGetProgramInfoLog(shaderProgram, sizeof(log), nullptr, log);
        std::cerr << "Shader program failed to link: " << log << std::endl;
        exit(EXIT_FAILURE);
    }
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
	else 
	{
		std::cerr << "Uniform '" << name << "' not found or inactive in shader program " << shaderProgram << std::endl;
		exit(EXIT_FAILURE);
	}
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z) 
{
	use();

	int location = glGetUniformLocation(shaderProgram, name);
	if (location != -1) {
		glUniform3f(location, x, y, z);
	}
	else
	{
		std::cerr << "Uniform '" << name << "' not found or inactive in shader program " << shaderProgram << std::endl;
		exit(EXIT_FAILURE);
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
	else 
	{
		std::cerr << "Uniform '" << name << "' not found or inactive in shader program " << shaderProgram << std::endl;
		exit(EXIT_FAILURE);
	}
}
void ShaderProgram::onCameraChanged(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& eye)
{
	setUniform("viewMatrix", view);
	setUniform("projectionMatrix", projection);

	GLint location = glGetUniformLocation(shaderProgram, "cameraPosition");

	if (location != -1)
	{
		setUniform("cameraPosition", eye.x, eye.y, eye.z);
	}
}


bool ShaderProgram::hasUniform(const char* name) const
{
    return glGetUniformLocation(shaderProgram, name) != -1;
}

void ShaderProgram::setUniformInt(const char* name, int value)
{
    use();
    GLint location = glGetUniformLocation(shaderProgram, name);
    if (location == -1)
    {
        std::cerr << "Uniform not found: " << name << std::endl;
        exit(EXIT_FAILURE);
    }
    glUniform1i(location, value);
}

void ShaderProgram::setMaterial(const Material& material)
{
    // Different shading models use different parts of the material.
    if (hasUniform("objectColor"))
        setUniform("objectColor", material.color.x, material.color.y, material.color.z);
    if (hasUniform("materialAmbient"))
        setUniform("materialAmbient", material.ambient.x, material.ambient.y, material.ambient.z);
    if (hasUniform("specularStrength"))
        setUniform("specularStrength", material.specularStrength);
    if (hasUniform("shininess"))
        setUniform("shininess", material.shininess);
}

void ShaderProgram::setLights(const std::vector<std::unique_ptr<Light>>& lights)
{
    // Unlit programs (signature, clocks, etc.) do not use this list.
    if (!hasUniform("lightCount")) return;

    setUniformInt("lightCount", static_cast<int>(lights.size()));
    for (size_t i = 0; i < lights.size(); ++i)
    {
        const Light& light = *lights[i];
        std::string index = "[" + std::to_string(i) + "]";
        setUniform(("lightPositions" + index).c_str(), light.position.x, light.position.y, light.position.z);
        setUniform(("lightColors" + index).c_str(), light.color.x, light.color.y, light.color.z);
        if (hasUniform(("lightAttenuations" + index).c_str()))
            setUniform(("lightAttenuations" + index).c_str(), light.attenuationFactors.x, light.attenuationFactors.y, light.attenuationFactors.z);
    }
}
