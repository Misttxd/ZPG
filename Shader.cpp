#include "Shader.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

Shader::Shader() : shaderID(0)
{
}

void Shader::attachTo(GLuint programId)
{
    glAttachShader(programId, shaderID);
}   