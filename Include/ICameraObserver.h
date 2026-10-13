#pragma once

#include <glm/mat4x4.hpp>

class ICameraObserver
{
public:
    virtual ~ICameraObserver() = default;

    virtual void onCameraChanged(const glm::mat4& view, const glm::mat4& projection) = 0; //child class has to implement
};