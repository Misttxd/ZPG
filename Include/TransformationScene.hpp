#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"
#include "SceneSignature.hpp"
#include <utility>

class TransformationScene : public Scene
{
public:
    TransformationScene() : Scene("Clock")
    {
        createCamera();
        ShaderProgram& clockShader = addShaderProgram("shaders/clock.vert", "shaders/right.frag");

        DrawableObject& clock = addObject(DrawableObjectFactory::create(ObjectType::Clock, clockShader));

        clock.transformation.scale(0.8f, 0.8f, -0.8f);
    }
};
