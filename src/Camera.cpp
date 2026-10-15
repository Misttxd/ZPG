#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <cmath>

Camera::Camera()
{
    viewMatrix = glm::lookAt(eye, eye + target, up);
    setPerspective(800, 600);;
}

void Camera::setPerspective(int width, int height)
{
    if (width <= 0 || height <= 0)
        return;

    projectionMatrix = glm::perspective(glm::radians(60.0f), static_cast<float>(width) / height,
        0.1f,
        100.0f
    );

    notifyObservers();
}


void Camera::addObserver(ICameraObserver& observer)
{
    observers.push_back(&observer);
    observer.onCameraChanged(viewMatrix, projectionMatrix);
}

void Camera::clearObservers()
{
    observers.clear();
}

void Camera::notifyObservers()
{
    for (ICameraObserver* observer : observers)
    {
        observer->onCameraChanged(viewMatrix, projectionMatrix);
    }
}

void Camera::move(float forward, float sideways, float vertical, double deltaTime)
{
    if (forward == 0.0f && sideways == 0.0f && vertical == 0.0f)
    {
        return;
    }

    glm::vec3 front = glm::normalize(glm::vec3(target.x, 0.0f, target.z));
    glm::vec3 right = glm::normalize(glm::cross(front, up));


    glm::vec3 direction = front * forward + right * sideways + up * vertical;

   
    eye += glm::normalize(direction) * speed * static_cast<float>(deltaTime);

    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyObservers();
}

void Camera::rotate(float deltaX, float deltaY)
{
    const float sensitivity = 0.1f;

    alpha += deltaY * sensitivity;
    fi += deltaX * sensitivity;

    alpha = std::clamp(alpha, 1.0f, 179.0f);
    fi = std::fmod(fi, 360.0f);

    if (fi < 0.0f)
        fi += 360.0f;

    float a = glm::radians(alpha);
    float f = glm::radians(fi);

    target.x = std::sin(a) * std::cos(f);
    target.y = std::cos(a);
    target.z = std::sin(a) * std::sin(f);

    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyObservers();
}

void Camera::setSpeed(float speed) {
    this->speed = std::max(0.1f, speed);
}

float Camera::getSpeed() const {
    return speed;
}
