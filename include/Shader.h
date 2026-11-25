#pragma once

#include <glad/gl.h>

class Shader
{
public:
    Shader();
    ~Shader();

    void createShaderFromFile(GLenum shaderType, const char* shaderFile);
    void attachTo(GLuint programId);

private:
    GLuint shaderID;
};