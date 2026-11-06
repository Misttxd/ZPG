#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"

class CV72aScene : public Scene
{
public:
    CV72aScene() : Scene("CV7 2a")
    {
        createCamera();
        auto& program = addShaderProgram("shaders/lighting.vert", "shaders/cv7Wrong.frag");
        auto& ball = addObject(DrawableObjectFactory::create(ObjectType::Sphere, program));
        ball.transformation.scale(0.8f);
        ball.material.color = glm::vec3(0.385f, 0.647f, 0.812f);
        ball.material.ambient = glm::vec3(0.025f);
        ball.material.specularStrength = 1.0f;
        ball.material.shininess = 1.0f;
        addLight().position = glm::vec3(0.0f, 0.0f, -3.0f);
    }
};
