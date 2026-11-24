#pragma once

#include "Transformation.h"
#include <glm/mat4x3.hpp>
#include <cmath>
#include <cstddef>
#include <vector>

class PathController
{
public:
    void moveLine(Transformation& transformation, float duration)
    {
        begin(transformation, duration, 2);
    }

    void moveBezier(Transformation& transformation, float duration)
    {
        begin(transformation, duration, 4);
    }

    bool addPoint(const glm::vec3& point)
    {
        if (!target || points.size() >= requiredCount)
        {
            return false;
        }

        points.push_back(point);
        if (points.size() != requiredCount)
        {
            return false;
        }

        target->setPosition(points.front());
        return true;
    }

    void update(double deltaTime)
    {
        if (!target || points.size() != requiredCount)
        {
            return;
        }

        phase = std::fmod(phase + deltaTime / duration, 2.0);
        float t = static_cast<float>(phase);
        if (t > 1.0f)
        {
            t = 2.0f - t;
        }

        target->setPosition(getPoint(t));
    }

private:
    void begin(Transformation& transformation, float duration, std::size_t count)
    {
        target = &transformation;
        this->duration = duration;
        requiredCount = count;
        points.clear();
        phase = 0.0;
    }

    glm::vec3 getPoint(float t) const
    {
        if (requiredCount == 2)
        {
            return points[0] + t * (points[1] - points[0]);
        }

        glm::mat4 A = glm::mat4(
            glm::vec4(-1.0, 3.0, -3.0, 1.0),
            glm::vec4(3.0, -6.0, 3.0, 0),
            glm::vec4(-3.0, 3.0, 0, 0),
            glm::vec4(1, 0, 0, 0));

        glm::mat4x3 B(points[0], points[1], points[2], points[3]);
        glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
        glm::vec3 p = parameters * A * glm::transpose(B);
        return p;
    }

    Transformation* target = nullptr;
    float duration = 1.0f;
    std::size_t requiredCount = 0;
    std::vector<glm::vec3> points;
    double phase = 0.0;
};
