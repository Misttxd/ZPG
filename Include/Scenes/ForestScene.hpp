#pragma once

#include "Scene.h"
#include "SceneSignature.hpp"
#include "DrawableObjectFactory.h"
#include <cstdlib>
#include <cmath>
#include "camera.h"
#include <GLFW/glfw3.h>

class ForestScene : public Scene
{
public:
    ForestScene() : Scene("Forest")
    {
        createCamera();
        ShaderProgram& treeProgram = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        treeProgram.setUniformInt("isTree", 1);
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

        for (int i = 0; i < treeCount; i++)
        {
            DrawableObject& tree = addObject(DrawableObjectFactory::create(ObjectType::Tree, treeProgram));
            tree.material = forestMaterial;
            tree.transformation.translate(randomFloat(-10.0f, 10.0f), -1.5f, randomFloat(-25.0f, -2.0f));
            tree.transformation.rotate(randomFloat(0.0f, 360.0f), 0.0f, 1.0f, 0.0f);
            tree.transformation.scale(0.4f * randomFloat(0.6f, 1.2f));
        }

        for (int i = 0; i < bushesCount; i++)
        {
            DrawableObject& bush = addObject(DrawableObjectFactory::create(ObjectType::Bush, groundProgram));
            bush.material = forestMaterial;
            bush.material.color = glm::vec3(0.27f, 0.70f, 0.12f);
            bush.transformation.translate(randomFloat(-10.0f, 10.0f), -1.5f, randomFloat(-25.0f, -2.0f));
            bush.transformation.scale(2.0f * randomFloat(0.9f, 1.1f));
        }

        for (int i = 0; i < FireFlyCount; i++)
        {
            Firefly& firefly = fireflies[i];
            firefly.light = &addLight(Light::point(glm::vec3(0.0f) /*pos*/, glm::vec3(1.0f, 0.85f, 0.3f) /*color*/, glm::vec3(1.0f, 0.3f, 0.4f) /*attensudaus*/));

            firefly.object = &addObject(DrawableObjectFactory::create(ObjectType::Sphere, fireflyProgram));
            firefly.object->material.color = firefly.light->color;

            moveFirefly(i);
        }

        addLight(Light::directional(glm::vec3(-1.0f, -1.0f, -1.0f),     glm::vec3(0.1f)));


        flashlight = &addLight(Light::spot(
            getCamera()->getPosition(),    // poloha jako pocatecni poloha kamery
            glm::vec3(0.0f, 0.0f, 0.0f),   // smer dopredu a trochu dolu
            glm::vec3(1.0f),               // barva a intenzita
            glm::vec3(1.0f, 0.05f, 0.01f)  // konstantni, linearni a kvadraticky utlum
        ));


        addSignature(*this);
    }

    void update(double deltaTime, float clockTime) override
    {
        Scene::update(deltaTime, clockTime);

        fireflyTime += static_cast<float>(deltaTime);
        for (int i = 0; i < FireFlyCount; i++)
        {
            moveFirefly(i);
        }

        flashlight->position = getCamera()->getPosition();
        flashlight->direction = getCamera()->getDirection();
    }

    void onKeyPressed(int key) override
    {
        if (key == GLFW_KEY_F)
        {
            flashlightOn = !flashlightOn;

            if (flashlightOn == true)
            {
                flashlight->color = glm::vec3(0.9f);
            }
            else if (flashlightOn == false)
            {
                flashlight->color = glm::vec3(0.0f);
            }
        }
    }

private:


    struct Firefly
    {
        Light* light;
        DrawableObject* object;
    };
    static constexpr int FireFlyCount = 2;
    Firefly fireflies[FireFlyCount] = {};

    Light* flashlight = nullptr;



    float fireflyTime = 0.0f;
    bool flashlightOn = true;

    void moveFirefly(int i)
    {
        Firefly& firefly = fireflies[i];
        float t = fireflyTime * 0.7f + i * 3.14f;
        firefly.light->position = glm::vec3(2.0f * std::sin(t), -0.2f + 0.4f * std::sin(2.0f * t), -6.0f + 1.5f * std::cos(t));

        const glm::vec3& position = firefly.light->position;
        firefly.object->transformation.clear();
        firefly.object->transformation.translate(position.x, position.y, position.z);
        firefly.object->transformation.scale(0.06f);
    }

    static float randomFloat(float min, float max)
    {
        return min + (max - min) * (static_cast<float>(std::rand()) / RAND_MAX);
    }
};
