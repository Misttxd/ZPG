#pragma once

#include "ITransformation.hpp"
#include <glm/mat4x3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <vector>

class PathTransformation : public ITransformation
{
public:
    void begin(float duration)
    {
        this->duration = duration;
        points.clear();
        startTime = 0.0;
    }

    bool isReady() const
    {
        if (points.size() == 4)
        {
            return true;
        }
        else if (points.size() != 4)
        {
            return false;
        }
        else
        {
            //bad
        }
    }

    bool addPoint(const glm::vec3& point, double time)
    {
        if (isReady() == true)
        {
            return false;
        }

        points.push_back(point);

        if (isReady() == true)
        {
            startTime = time;
            return true;
        }

        return false;
    }

    const std::vector<glm::vec3>& getPoints() const
    {
        return points;
    }

    void setPoint(int index, const glm::vec3& point)
    {
        points[index] = point;
    }

    glm::mat4 getMatrix(double time = 0.0) const override
    {
        if (isReady() == false)
        {
            return glm::mat4(1.0f);
        }

        float t = static_cast<float>(std::fmod((time - startTime) / duration, 2.0));

        if (t > 1.0f)
        {
            t = 2.0f - t;
        }

        return glm::translate(glm::mat4(1.0f), getPoint(t));
    }

private:
    glm::vec3 getPoint(float t) const
    {
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

    std::vector<glm::vec3> points;
    float duration = 1.0f;
    double startTime = 0.0;
};