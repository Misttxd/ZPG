#pragma once

#include <glm/glm.hpp>

class BezierCurve
{
public:
    BezierCurve(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3) : B(p0, p1, p2, p3)
    {
    }

    glm::vec3 getPoint(float t) const
    {
        glm::mat4 A = glm::mat4(
            glm::vec4(-1.0, 3.0, -3.0, 1.0),
            glm::vec4(3.0, -6.0, 3.0, 0),
            glm::vec4(-3.0, 3.0, 0, 0),
            glm::vec4(1, 0, 0, 0));

        glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
        glm::vec3 p = parameters * A * glm::transpose(B);

        return p;
    }

private:
    glm::mat4x3 B;
};