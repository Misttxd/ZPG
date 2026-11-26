#pragma once

#include "../Scene.h"
#include "DrawableObjectFactory.h"
#include "camera.h"

class CV72dScene : public Scene
{
public:
    CV72dScene() : Scene("CV7 2d")
    {
        createCamera();
        auto& program = addShaderProgram("shaders/lighting.vert", "shaders/cv7Correct.frag");
        auto& ball = addObject(DrawableObjectFactory::create(ObjectType::Sphere, program));
        ball.transformation.scale(0.8f);
        ball.material.color = glm::vec3(0.385f, 0.647f, 0.812f);
        addLight().position = glm::vec3(2.0f, 2.0f, 3.0f);
    }
};
