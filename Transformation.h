#pragma once
#include "ShaderProgram.h"

#include "ITransformation.hpp"




#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>

//class Transformation
//{
//public:
//	Transformation();
//	
//	void setTranslation(float x, float y, float z);
//	void setScale(float scale);
//	void setRotation(float rotation);
//	void rotate(float angle);
//
//	void apply(ShaderProgram* shaderProgram);
//
//	void add(const Transformation& transformation);
//	void setRotationAxis(float x, float y, float z);
//	void setRotationSpeed(float speed);
//	void update(float deltaTime);
//
//private:
//	float translationX;
//	float translationY;
//	float translationZ;
//	float scale;
//	float rotation;
//
//	glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
//	float rotationSpeed = 0.0f;
//	std::vector<Transformation> transformations;
//
//	glm::mat4 calculateMatrix() const;
//};

class Transformation {
public:
    void translate(float x, float y, float z);

    void rotate(float degrees, float x, float y, float z);

    void scale(float x, float y, float z);

    void clear();

    glm::mat4 getMatrix() const;

private:
    std::vector<std::unique_ptr<ITransformation>> operations;
};