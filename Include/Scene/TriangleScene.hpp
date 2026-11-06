#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"
#include "SceneSignature.hpp"

class TriangleScene : public Scene
{
public:
    TriangleScene(bool translationFirst = true) : Scene(translationFirst ? "Triangle: T * R" : "Triangle: R * T")
    {
        ShaderProgram& basic = addShaderProgram("shaders/right.vert", "shaders/right.frag");
        DrawableObject& triangle = addObject(DrawableObjectFactory::create(ObjectType::Triangle, basic));
        if (translationFirst)
        {
            triangle.transformation.translate(0.45f, 0.0f, 0.0f);
            triangle.transformation.rotate(60.0f, 0.0f, 0.0f, 1.0f);
        }
        else
        {
            triangle.transformation.rotate(60.0f, 0.0f, 0.0f, 1.0f);
            triangle.transformation.translate(0.45f, 0.0f, 0.0f);
        }
        triangle.transformation.scale(0.65f);
        addSignature(*this);
    }
};
