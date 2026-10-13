#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <vector>
#include "ICameraObserver.h"

#include <glm/geometric.hpp> //movement

class Camera
{
public:
	Camera();

	void setPerspective(int width, int height);

	void addObserver(ICameraObserver& observer);
	void clearObservers();

	void move(float forward, float sideways, float vertical, double deltaTime); //movement

	float speed = 3.0f; //TODO - make private
	void rotate(float deltaX, float deltaY);



private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec3 eye{ 0.0f, 1.6f, 3.0f };
	glm::vec3 target{ 0.0f, 0.0f, -1.0f };
	glm::vec3 up{ 0.0f, 1.0f, 0.0f };

	std::vector<ICameraObserver*> observers;
	void notifyObservers();


	//roatations
	float alpha = 90.0f;
	float fi = 270.0f;

	

	
};