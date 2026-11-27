#pragma once

#include "ForestScene.hpp"
#include <cstdio>
#include <vector>

#include "PathTransformation.hpp"

#include <algorithm>
#include <cmath>

class CV11Scene : public ForestScene
{
public:
    CV11Scene() : ForestScene("CV11")
    {
        ShaderProgram& program = addShaderProgram("shaders/lighting.vert", "shaders/ambient.frag");

        pointProgram = &program;

        ball = &addObject(DrawableObjectFactory::create(ObjectType::Sphere, program));

        ball->material.color = glm::vec3(1.0f, 0.4f, 0.0f);

        path = ball->transformation.moveBezier(4.0f);
        ball->transformation.scale(0.2f);
    }

    void onWorldClick(GLuint index, const glm::vec3& pos) override
    {
        DrawableObject* object = findObject(index);

        if (!object) //out out world
        {
            return;
        }

        path->addPoint(pos, elapsedTime);
        DrawableObject& marker = addObject(DrawableObjectFactory::create(ObjectType::Sphere, *pointProgram));

        marker.material.color = glm::vec3(0.0f, 1.0f, 1.0f);
        marker.transformation.translate(pos.x, pos.y, pos.z);
        marker.transformation.scale(0.08f);

        pointMarkers.push_back(&marker);



       
        bool ready = path->isReady();

        if (ready == true)
        {
      
            for (DrawableObject* pointMarker : pointMarkers)
            {
                pointMarker->material.color = glm::vec3(0.0f, 1.0f, 0.0f); //green
            }

            std::puts("Ctvrty bod zadan, pohyb zacina.");
        }

        else if (ready == false)
        {
            for (DrawableObject* pointMarker : pointMarkers)
            {
                pointMarker->material.color = glm::vec3(0.0f, 1.0f, 1.0f); //azure
            }
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

    PathTransformation* path = nullptr;

    ShaderProgram* pointProgram = nullptr;
    std::vector<DrawableObject*> pointMarkers;
};