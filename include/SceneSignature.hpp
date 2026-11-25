#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"

inline void addSignature(Scene& scene)
{
    ShaderProgram& shader = scene.addShaderProgram("shaders/lighting.vert", "shaders/signature.frag", false);
    shader.setUniform("viewMatrix", glm::mat4(1.0f));
    shader.setUniform("projectionMatrix", glm::mat4(1.0f));


    DrawableObject& signature = scene.addObject(DrawableObjectFactory::create(ObjectType::Login, shader));
    signature.alwaysOnTop = true;
    signature.transformation.translate(0.65f, -0.92f, 0.0f);
    signature.transformation.scale(0.080f);

}
