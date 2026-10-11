#pragma once

#include "Scene.h"
#include "SceneSignature.hpp"
#include "../Objects/DrawableObjectFactory.h"
#include <cstdlib>

class ForestScene : public Scene
{
public:
    ForestScene() : Scene("Forest")
    {
        ShaderProgram& trees = addShaderProgram("shaders/right.vert", "shaders/right.frag");
        ShaderProgram& bushes = addShaderProgram("shaders/right.vert", "shaders/basic.frag");
        ShaderProgram& sun = addShaderProgram("shaders/right.vert", "shaders/right.frag");
        bushes.setUniform("baseColor", 0.27f, 0.70f, 0.12f);

        const int objectsPerType = 11;

        for (int i = 0; i < objectsPerType; ++i)
        {
            DrawableObject& tree = addObject(DrawableObjectFactory::create(ObjectType::Tree, trees));
            tree.transformation.translate(randomFloat(-0.85f, 0.85f), randomFloat(-0.75f, 0.35f), 0.0f);
            tree.transformation.scale(0.045f * randomFloat(0.9f, 1.1f));
        }

        for (int i = 0; i < objectsPerType; ++i)
        {
            DrawableObject& bush = addObject(DrawableObjectFactory::create(ObjectType::Bush, bushes));
            bush.transformation.translate(randomFloat(-0.85f, 0.85f), randomFloat(-0.75f, 0.35f), 0.0f);
            bush.transformation.scale(0.5f * randomFloat(0.9f, 1.1f));
        }

        DrawableObject& sunObject = addObject(DrawableObjectFactory::create(ObjectType::Sun, sun));
        sunObject.transformation.translate(0.8f, 0.8f, 0.0f);
        sunObject.transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, 12.0f);
        sunObject.transformation.scale(0.2f);
        addSignature(*this);
    }

private:
    static float randomFloat(float min, float max)
    {
        return min + (max - min) * (static_cast<float>(std::rand()) / RAND_MAX);
    }
};
