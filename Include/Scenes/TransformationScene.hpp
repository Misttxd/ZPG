#pragma once

#include "Scene.h"
#include "../Objects/DrawableObjectFactory.h"
#include "SceneSignature.hpp"
#include <utility>

class TransformationScene : public Scene
{
public:
    TransformationScene() : Scene("Ukazka transformaci")
    {
        const char* vertexFile = "shaders/right.vert";
        const char* colorFile = "shaders/basic.frag";
        const char* normalFile = "shaders/right.frag";

        ShaderProgram& normalProgram = addShaderProgram(vertexFile, normalFile);
        ShaderProgram& yellowProgram = addShaderProgram(vertexFile, colorFile);
        yellowProgram.setUniform("baseColor", 1.0f, 1.0f, 0.0f);

        DrawableObject& leftSphere = addObject(DrawableObjectFactory::create(ObjectType::Sphere, normalProgram));
        leftSphere.transformation.translate(-0.55f, -0.25f, 0.0f);
        leftSphere.transformation.rotate(30.0f, 0.0f, 1.0f, 0.0f, 30.0f);
        leftSphere.transformation.scale(0.25f, 0.25f, 0.25f);

        DrawableObject& rightSphere = addObject(DrawableObjectFactory::create(ObjectType::Sphere, normalProgram));
        rightSphere.transformation.translate(0.45f, -0.25f, 0.0f);

        Transformation shape;
        shape.rotate(35.0f, 0.0f, 0.0f, 1.0f, -20.0f);
        shape.scale(0.35f, 0.18f, 0.25f);
        rightSphere.transformation.add(std::move(shape));

        DrawableObject& sunObject = addObject(DrawableObjectFactory::create(ObjectType::Sphere, yellowProgram));
        sunObject.transformation.translate(0.0f, 0.5f, 0.0f);
        sunObject.transformation.scale(0.18f, 0.18f, 0.18f);
        addSignature(*this);
    }
};
