#include "Model.h"

Model::Model(const float* data, int velikostBajtu, int pocetVrcholu, GLenum typPrimitiva)
{
	this->pocetVrcholu = pocetVrcholu;
	this->typPrimitiva = typPrimitiva;

    VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, velikostBajtu, data, GL_STATIC_DRAW);

    VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(typPrimitiva, 0, pocetVrcholu);
}