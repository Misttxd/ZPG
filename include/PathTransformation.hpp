#pragma once

#include "ITransformation.hpp"

#include "BezierCurve.hpp"

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
        else if (points.size() >= 4 && (points.size() - 4) % 3 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void addPoint(const glm::vec3& point, double time)
    {
        points.push_back(point);

        if (isReady() == true)
        {
            startTime = time;
        }
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
        int curveCount = static_cast<int>((points.size() - 1) / 3);

        float curveT = t * static_cast<float>(curveCount);
        int curveIndex = static_cast<int>(curveT);

        if (curveIndex == curveCount)
        {
            curveIndex--;
        }

        float localT = curveT - static_cast<float>(curveIndex);
        int firstPoint = curveIndex * 3;

        BezierCurve curve(
            points[firstPoint],
            points[firstPoint + 1],
            points[firstPoint + 2],
            points[firstPoint + 3]);

        return curve.getPoint(localT);
    }

    std::vector<glm::vec3> points;
    float duration = 1.0f;
    double startTime = 0.0;
};