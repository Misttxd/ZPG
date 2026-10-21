#pragma once

#include "Scene.h"
#include "SceneSignature.hpp"
#include "DrawableObjectFactory.h"
#include <cstdlib>

#include <chrono>
#include <ctime>

#include <GLFW/glfw3.h>


class ForestScene : public Scene
{
public:
    ForestScene() : Scene("Forest")
    {
        createCamera();
        ShaderProgram& trees = addShaderProgram("shaders/right.vert", "shaders/right.frag");
        ShaderProgram& bushes = addShaderProgram("shaders/right.vert", "shaders/basic.frag");
        ShaderProgram& sun = addShaderProgram("shaders/right.vert", "shaders/right.frag");

        ShaderProgram& treeAdvanced = addShaderProgram("shaders/TreeShader.vert", "shaders/TreeShader.frag");

        ShaderProgram& clockShaderD = addShaderProgram("shaders/clock.vert", "shaders/right.frag");

        bushes.setUniform("baseColor", 0.27f, 0.70f, 0.12f);

        ShaderProgram& groundShader = addShaderProgram("shaders/right.vert", "shaders/basic.frag");
        groundShader.setUniform("baseColor", 0.35f, 0.22f, 0.10f);

        DrawableObject& ground = addObject(DrawableObjectFactory::create(ObjectType::Ground, groundShader));

        ground.transformation.translate(0.0f, -1.5f, -13.5f);
        ground.transformation.scale(50.0f);

        const int bushesCount = 20;
        const int treeCount = 74;

        for (int i = 0; i < treeCount; ++i) //trees
        {
            DrawableObject& tree = addObject(DrawableObjectFactory::create(ObjectType::Tree, treeAdvanced));
            tree.transformation.translate(randomFloat(-10.0f, 10.0f), -1.5f, randomFloat(-25.0f, -2.0f));
            tree.transformation.rotate(randomFloat(0.0f, 360.0f), 0.0f, 1.0f, 0.0f);
            tree.transformation.scale(0.4f * randomFloat(0.6f, 1.2f));

        }

        for (int i = 0; i < bushesCount; ++i) //bushes
        {
            DrawableObject& bush = addObject(DrawableObjectFactory::create(ObjectType::Bush, bushes));
            bush.transformation.translate(randomFloat(-10.0f, 10.0f), -1.5f, randomFloat(-25.0f, -2.0f));
            bush.transformation.scale(2.0f * randomFloat(0.9f, 1.1f));
        }

        DrawableObject& sunObject = addObject(DrawableObjectFactory::create(ObjectType::Sun, sun));
        sunObject.transformation.translate(8.0f, 9.0f, -18.0f);
        sunObject.transformation.scale(1.2f);
        sunObject.transformation.scale(0.5f);
        addSignature(*this);



        ShaderProgram& clockShader = addShaderProgram("shaders/clock.vert", "shaders/right.frag");
        clockProgram = &clockShader;
         
        DrawableObject& firstClock = addObject(DrawableObjectFactory::create(ObjectType::Clock, clockShader));
        firstClock.transformation.translate(-3.0f, 0.5f, -6.0f);
        firstClock.transformation.scale(0.8f, 0.8f, -0.8f);
        firstClock.transformation.scale(0.9, 0.8, -0.8);

        DrawableObject& secondClock = addObject(DrawableObjectFactory::create(ObjectType::Clock, clockShader));
        secondClock.transformation.translate(4.0f, 0.5f, -14.0f);
        secondClock.transformation.scale(0.8f, 0.8f, -0.8f);
    }

    void update(double deltaTime, float clockTime) override
    {
        Scene::update(deltaTime, clockTime);

        int elapsedSeconds = static_cast<int>(clockTime - startTime);
        clockProgram->setUniform("time", seconds + elapsedSeconds);
    }

private:
    static float randomFloat(float min, float max)
    {
        return min + (max - min) * (static_cast<float>(std::rand()) / RAND_MAX);
    }

    ShaderProgram* clockProgram = nullptr;

    static int getCurrentTime()
    {
        std::time_t now = std::time(nullptr);
        std::tm local{};
        localtime_s(&local, &now);

        return (local.tm_hour % 12) * 3600
            + local.tm_min * 60
            + local.tm_sec;
    }

    int seconds = getCurrentTime();
    double startTime = glfwGetTime();
};
