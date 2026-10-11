#include "../Transformation.h"

#include <cassert>
#include <cmath>
#include <stdexcept>

void expectPoint(const Transformation& transformation, const glm::vec4& input,
                 const glm::vec4& expected)
{
    glm::vec4 actual = transformation.getMatrix() * input;
    for (int i = 0; i < 4; ++i)
    {
        assert(std::abs(actual[i] - expected[i]) < 0.0001f);
    }
}

int main()
{
    Transformation transformation;
    const glm::vec4 point(1, 0, 0, 1);
    expectPoint(transformation, point, point);

    transformation.translate(2, 0, 0);
    transformation.scale(0.5f, 0.5f, 0.5f);
    expectPoint(transformation, point, glm::vec4(2.5f, 0, 0, 1));
    // Reading the matrix does not consume or change the transformation.
    expectPoint(transformation, point, glm::vec4(2.5f, 0, 0, 1));

    transformation.clear();
    expectPoint(transformation, point, point);
    transformation.scale(0.5f, 0.5f, 0.5f);
    transformation.translate(2, 0, 0);
    expectPoint(transformation, point, glm::vec4(1.5f, 0, 0, 1));

    transformation.clear();
    transformation.rotate(90, 0, 0, 2);
    transformation.translate(2, 0, 0);
    transformation.rotate(90, 0, 0, 1);
    transformation.scale(0.5f, 0.5f, 0.5f);
    expectPoint(transformation, point, glm::vec4(-0.5f, 2, 0, 1));

    bool rejectedZeroAxis = false;
    try
    {
        transformation.rotate(90, 0, 0, 0);
    }
    catch (const std::invalid_argument&)
    {
        rejectedZeroAxis = true;
    }
    assert(rejectedZeroAxis);
    expectPoint(transformation, point, glm::vec4(-0.5f, 2, 0, 1));
}
