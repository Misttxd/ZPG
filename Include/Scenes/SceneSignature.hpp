#pragma once

#include "Scene.h"
#include "../Objects/DrawableObjectFactory.h"

inline void addSignature(Scene& scene)
{
    ShaderProgram& shader = scene.addShaderProgram("shaders/right.vert", "shaders/signature.frag");
    DrawableObject& signature = scene.addObject(DrawableObjectFactory::create(ObjectType::Login, shader));
    signature.transformation.translate(0.65f, -0.92f, -0.90f);
    signature.transformation.scale(0.080f);
}
