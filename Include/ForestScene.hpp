#pragma once

#include "Scene.h"
#include "SceneSignature.hpp"
#include "DrawableObjectFactory.h"
#include <cstdlib>

class ForestScene : public Scene
{
public:
    ForestScene() : Scene("Forest")
    {
        createCamera();
        ShaderProgram& trees = addShaderProgram("shaders/right.vert", "shaders/right.frag");
        ShaderProgram& bushes = addShaderProgram("shaders/right.vert", "shaders/basic.frag");
        ShaderProgram& sun = addShaderProgram("shaders/right.vert", "shaders/right.frag");
        bushes.setUniform("baseColor", 0.27f, 0.70f, 0.12f);

        ShaderProgram& groundShader = addShaderProgram("shaders/right.vert", "shaders/basic.frag");
        groundShader.setUniform("baseColor", 0.35f, 0.22f, 0.10f);

        DrawableObject& ground = addObject(DrawableObjectFactory::create(ObjectType::Ground, groundShader));

        ground.transformation.translate(0.0f, -1.5f, -13.5f);
        ground.transformation.scale(500.0f);

        const int bushesCount = 20;
        const int treeCount = 74;

        for (int i = 0; i < treeCount; ++i) //trees
        {
            DrawableObject& tree = addObject(DrawableObjectFactory::create(ObjectType::Tree, trees));
            tree.transformation.translate(randomFloat(-10.0f, 10.0f), -1.5f, randomFloat(-25.0f, -2.0f));
            tree.transformation.rotate(randomFloat(0.0f, 360.0f), 0.0f, 1.0f, 0.0f);
            tree.transformation.scale(0.4f * randomFloat(0.6f, 1.2f));

        }

        for (int i = 0; i < bushesCount; ++i) //bushes
        {
            DrawableObject& bush = addObject(DrawableObjectFactory::create(ObjectType::Bush, bushes));
            bush.transformation.translate(randomFloat(-10.0f, 10.0f), -1.5f, randomFloat(-25.0f, -2.0f));
            bush.transformation.scale(2.0f * randomFloat(0.9f, 1.1f));
        }

        DrawableObject& sunObject = addObject(DrawableObjectFactory::create(ObjectType::Sun, sun));
        sunObject.transformation.translate(8.0f, 9.0f, -18.0f);
        sunObject.transformation.scale(1.2f);
        sunObject.transformation.scale(0.5f);
        addSignature(*this);

        ShaderProgram& clockShader = addShaderProgram("shaders/clock.vert", "shaders/right.frag");

        DrawableObject& clock = addObject(DrawableObjectFactory::create(ObjectType::Clock, clockShader));

        clock.transformation.translate(0.0f, 10.0f, -1.0f);
        clock.transformation.rotate(180.0f, 0.0f, 1.0f, 0.0f);
        clock.transformation.scale(0.8f);
    }

private:
    static float randomFloat(float min, float max)
    {
        return min + (max - min) * (static_cast<float>(std::rand()) / RAND_MAX);
    }
};
