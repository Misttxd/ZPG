#include "PathController.hpp"
#include <glm/geometric.hpp>
#include <cassert>

int main()
{
    Transformation transformation;
    transformation.translate(-3.0f, -0.8f, -6.0f);
    transformation.rotate(30.0f, 0.0f, 1.0f, 0.0f);
    transformation.scale(0.2f);
    const glm::mat3 shape(transformation.getMatrix());

    auto expectPosition = [&](const glm::vec3& expected)
    {
        const glm::mat4 matrix = transformation.getMatrix();
        assert(glm::length(glm::vec3(matrix[3]) - expected) < 0.0001f);
        for (int i = 0; i < 3; i++)
        {
            assert(glm::length(glm::vec3(matrix[i]) - shape[i]) < 0.0001f);
        }
    };

    PathController controller;
    controller.update(10.0);
    assert(!controller.addPoint(glm::vec3(0.0f)));
    controller.moveLine(transformation, 2.0f);
    assert(!controller.addPoint(glm::vec3(0.0f)));
    controller.update(10.0);
    expectPosition(glm::vec3(-3.0f, -0.8f, -6.0f));
    assert(controller.addPoint(glm::vec3(4.0f, 2.0f, -2.0f)));
    expectPosition(glm::vec3(0.0f));
    controller.update(1.0);
    expectPosition(glm::vec3(2.0f, 1.0f, -1.0f));
    controller.update(1.0);
    expectPosition(glm::vec3(4.0f, 2.0f, -2.0f));
    controller.update(1.0);
    expectPosition(glm::vec3(2.0f, 1.0f, -1.0f));
    controller.update(1.0);
    expectPosition(glm::vec3(0.0f));

    controller.moveBezier(transformation, 2.0f);
    assert(!controller.addPoint(glm::vec3(0, 0, 0)));
    assert(!controller.addPoint(glm::vec3(2, 2, 0)));
    assert(!controller.addPoint(glm::vec3(3, 4, 0)));
    controller.update(10.0);
    assert(controller.addPoint(glm::vec3(6, 0, 0)));
    expectPosition(glm::vec3(0.0f));
    controller.update(1.0);
    expectPosition(glm::vec3(2.625f, 2.25f, 0.0f));
    assert(!controller.addPoint(glm::vec3(100.0f)));
    controller.update(1.0);
    expectPosition(glm::vec3(6, 0, 0));
    controller.update(1.0);
    expectPosition(glm::vec3(2.625f, 2.25f, 0.0f));
    controller.update(1.0);
    expectPosition(glm::vec3(0.0f));

    controller.moveLine(transformation, 2.0f);
    controller.update(1.0);
    expectPosition(glm::vec3(0.0f));
    assert(!controller.addPoint(glm::vec3(1.0f)));
    assert(controller.addPoint(glm::vec3(3.0f)));
    expectPosition(glm::vec3(1.0f));
    controller.update(1.0);
    expectPosition(glm::vec3(2.0f));

}
