#pragma once

#include "ForestScene.hpp"
#include <cstdio>
#include <vector>

class CV11Scene : public ForestScene
{
public:
    CV11Scene() : ForestScene("CV11")
    {
        ShaderProgram& program = addShaderProgram("shaders/lighting.vert", "shaders/ambient.frag");

        pointProgram = &program;

        ball = &addObject(DrawableObjectFactory::create(ObjectType::Sphere, program));

        ball->material.color = glm::vec3(1.0f, 0.4f, 0.0f);

        ball->transformation.moveBezier(4.0f);
        ball->transformation.scale(0.2f);
    }

    void onWorldClick(GLuint index, const glm::vec3& pos) override
    {
        DrawableObject* object = findObject(index);

        if (!object /*|| object->type != ObjectType::TexturedGround*/)
        {
            return;
        }

        if (ball->transformation.getPathPoints().size() == 4)
        {
            return;
        }

        bool ready = ball->transformation.addPathPoint(pos, elapsedTime);

        DrawableObject& marker = addObject(DrawableObjectFactory::create(ObjectType::Sphere, *pointProgram));

        marker.material.color = glm::vec3(0.0f, 1.0f, 1.0f); //azure
        marker.transformation.translate(pos.x, pos.y, pos.z);
        marker.transformation.scale(0.08f);

        pointMarkers.push_back(&marker);

        if (ready)
        {
            for (DrawableObject* pointMarker : pointMarkers)
            {
                pointMarker->material.color = glm::vec3(0.0f, 1.0f, 0.0f); //green
            }

            std::puts("Ctvrty bod zadan, pohyb zacina.");
        }
    }

    void onKeyPressed(int key) override
    {
        ForestScene::onKeyPressed(key);

        if (key == GLFW_KEY_R)
        {
            for (DrawableObject* marker : pointMarkers)
            {
                removeObject(marker);
            }

            pointMarkers.clear();
            ball->transformation.moveBezier(4.0f);

            std::puts("Trasa resetovana. Zadej ctyri nove body.");
        }
    }
private:
    DrawableObject* ball = nullptr;

    ShaderProgram* pointProgram = nullptr;
    std::vector<DrawableObject*> pointMarkers;
};