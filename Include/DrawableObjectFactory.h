#pragma once

#include "DrawableObject.h"
#include <memory>

enum class ObjectType
{
    Triangle,
    Sphere,
    Sun,
    Earth,
    Moon
};

class DrawableObjectFactory
{
public:
    static std::unique_ptr<DrawableObject> create(ObjectType type, ShaderProgram& shaderProgram);
};
