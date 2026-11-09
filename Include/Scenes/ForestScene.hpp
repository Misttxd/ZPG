#pragma once

#include "Scene.h"
#include "SceneSignature.hpp"
#include "DrawableObjectFactory.h"
#include <cstdlib>
#include <cmath>

class ForestScene : public Scene
{
public:
    ForestScene() : Scene("Forest")
    {
        createCamera();
        ShaderProgram& treeProgram = addShaderProgram("shaders/forestLighting.vert", "shaders/forestLighting.frag");
        ShaderProgram& groundProgram = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        ShaderProgram& fireflyProgram = addShaderProgram("shaders/lighting.vert", "shaders/ambient.frag");

        Material forestMaterial;
        forestMaterial.ambient = glm::vec3(0.002f);
        forestMaterial.specularStrength = 0.05f;

        DrawableObject& ground = addObject(DrawableObjectFactory::create(ObjectType::Ground, groundProgram));
        ground.material = forestMaterial;
        ground.material.color = glm::vec3(0.35f, 0.22f, 0.10f);
        ground.transformation.translate(0.0f, -1.5f, -13.5f);
        ground.transformation.scale(50.0f);

        const int bushesCount = 20;
        const int treeCount = 74;

        for (int i = 0; i < treeCount; ++i)
        {
            DrawableObject& tree = addObject(DrawableObjectFactory::create(ObjectType::Tree, treeProgram));
            tree.material = forestMaterial;
            tree.transformation.translate(randomFloat(-10.0f, 10.0f), -1.5f, randomFloat(-25.0f, -2.0f));
            tree.transformation.rotate(randomFloat(0.0f, 360.0f), 0.0f, 1.0f, 0.0f);
            tree.transformation.scale(0.4f * randomFloat(0.6f, 1.2f));
        }

        for (int i = 0; i < bushesCount; ++i)
        {
            DrawableObject& bush = addObject(DrawableObjectFactory::create(ObjectType::Bush, groundProgram));
            bush.material = forestMaterial;
            bush.material.color = glm::vec3(0.27f, 0.70f, 0.12f);
            bush.transformation.translate(randomFloat(-10.0f, 10.0f), -1.5f, randomFloat(-25.0f, -2.0f));
            bush.transformation.scale(2.0f * randomFloat(0.9f, 1.1f));
        }

        fireflyLight = &addLight();
        fireflyLight->color = glm::vec3(1.0f, 0.85f, 0.3f);
        fireflyLight->attenuationFactors = glm::vec3(1.0f, 0.3f, 0.4f);

        firefly = &addObject(DrawableObjectFactory::create(ObjectType::Sphere, fireflyProgram));
        firefly->material.color = fireflyLight->color;

        moveFirefly();
        addSignature(*this);
    }

    void update(double deltaTime, float clockTime) override
    {
        Scene::update(deltaTime, clockTime);
        fireflyTime += static_cast<float>(deltaTime);
        moveFirefly();
    }

private:
    Light* fireflyLight = nullptr;
    DrawableObject* firefly = nullptr;
    float fireflyTime = 0.0f;

    void moveFirefly()
    {
        float t = fireflyTime * 0.7f;
        fireflyLight->position = glm::vec3(
            2.0f * std::sin(t),
            -0.2f + 0.4f * std::sin(2.0f * t),
            -6.0f + 1.5f * std::cos(t)
        );

        const glm::vec3& position = fireflyLight->position;
        firefly->transformation.clear();
        firefly->transformation.translate(position.x, position.y, position.z);
        firefly->transformation.scale(0.06f);
    }

    static float randomFloat(float min, float max)
    {
        return min + (max - min) * (static_cast<float>(std::rand()) / RAND_MAX);
    }
};
