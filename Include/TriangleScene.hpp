#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"

class TriangleScene : public Scene
{
public:
    TriangleScene() : Scene("Triangle")
    {
        ShaderProgram& basic = addShaderProgram("shaders/right.vert", "shaders/right.frag");
        addObject(DrawableObjectFactory::create(ObjectType::Triangle, basic));
    }
};
