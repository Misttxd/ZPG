#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>


class ICameraObserver
{
public:
    virtual ~ICameraObserver() = default;

    virtual void onCameraChanged(
        const glm::mat4& view,
        const glm::mat4& projection,
        const glm::vec3& eye
    ) = 0;
};