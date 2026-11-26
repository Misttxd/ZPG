#pragma once

#include "../Scene.h"
#include "DrawableObjectFactory.h"
#include "camera.h"

class CV72cScene : public Scene
{
public:
    CV72cScene() : Scene("CV7 2c")
    {
        createCamera();
        auto& program = addShaderProgram("shaders/lighting.vert", "shaders/cv7Correct.frag");
        auto& ball = addObject(DrawableObjectFactory::create(ObjectType::Sphere, program));
        ball.transformation.scale(0.8f);
        ball.material.color = glm::vec3(0.385f, 0.647f, 0.812f);
        addLight().position = glm::vec3(2.0f, 2.0f, 3.0f);
    }

    void update(double deltaTime, float clockTime) override
    {
        Scene::update(deltaTime, clockTime);
        glViewport(0, 0, 800, 600);
        getCamera()->setPerspective(800, 600);
    }
};
