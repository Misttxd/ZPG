#pragma once

#include "ForestScene.hpp"
#include "PathController.hpp"
#include <cstdio>

class CV11Scene : public ForestScene
{
public:
    CV11Scene() : ForestScene("CV11")
    {
        ShaderProgram& program =
            addShaderProgram("shaders/lighting.vert", "shaders/ambient.frag");

        ball = &addObject(DrawableObjectFactory::create(ObjectType::Sphere, program));

        ball->material.color = glm::vec3(1.0f, 0.4f, 0.0f);

        ball->transformation.translate(-3.0f, -0.8f, -6.0f);
        ball->transformation.scale(0.2f);

        pathController.moveBezier(ball->transformation, 4.0f);
        std::puts("CV11: klikni na 4 body na zemi. B = Bezier, L = usecka.");
    }

    void update(double deltaTime, float clockTime) override
    {
        ForestScene::update(deltaTime, clockTime);
        pathController.update(deltaTime);
    }

    void onWorldClick(GLuint index, const glm::vec3& pos) override
    {
        DrawableObject* object = findObject(index);
        if (!object || object->type != ObjectType::TexturedGround)
        {
            return;
        }

        if (pathController.addPoint(pos))
        {
            std::puts("Trasa hotova. Pro novou trasu stiskni B nebo L.");
        }
    }

    void onKeyPressed(int key) override
    {
        ForestScene::onKeyPressed(key);

        if (key == GLFW_KEY_B)
        {
            pathController.moveBezier(ball->transformation, 4.0f);
            std::puts("Bezier: klikni na 4 body na zemi.");
        }
        else if (key == GLFW_KEY_L)
        {
            pathController.moveLine(ball->transformation, 4.0f);
            std::puts("Usecka: klikni na 2 body na zemi.");
        }
    }

private:
    DrawableObject* ball = nullptr;
    PathController pathController;
};
