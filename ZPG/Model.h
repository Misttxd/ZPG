#pragma once
#include <GL/glew.h>

class Model
{
public:
    Model(const float* data, int velikostBajtu, int pocetVrcholu, GLenum typPrimitiva);
    ~Model();
    void draw();

private:
    GLuint VAO;
    GLuint VBO;
    int    pocetVrcholu;
    GLenum typPrimitiva;
};