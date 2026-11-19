#pragma once

#include "Scene.h"
#include "SceneSignature.hpp"
#include "DrawableObjectFactory.h"
#include <cstdlib>
#include <cmath>
#include "camera.h"
#include <GLFW/glfw3.h>

#include "Texture.h"
#include <algorithm>

class ForestScene : public Scene
{
public:
    ForestScene() : Scene("Forest")
    {
        createCamera();
        ShaderProgram& treeProgram = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        treeProgram.setUniformInt("isTree", 1);

        ShaderProgram& groundProgram = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        groundProgram.setUniformInt("useTexture", 1);
        groundProgram.setUniform("textureRepeat", 50.0f); //TODO L

        ShaderProgram& bushProgram = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        ShaderProgram& fireflyProgram = addShaderProgram("shaders/lighting.vert", "shaders/ambient.frag");
        shrekProgram = &addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        shrekProgram->setUniformInt("useTexture", 1);

        ShaderProgram& moonProgram = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        moon.object = &addObject(DrawableObjectFactory::create(ObjectType::Majoras_Mask, moonProgram));
        moonProgram.setUniformInt("useTexture", 1);
        moon.object->texture = moonTexture.getId();
        moon.object->transformation.translate(0.0f, 20.0f, -30.0f);
        moon.object->transformation.scale(0.1f);
        moon.object->transformation.rotate(0.0f, 0.0f, 0.0f, 1.0f); // Ikonický Zelda náklon hlavy do strany (roll)
        moon.object->transformation.rotate(25.0f, 1.0f, 0.0f, 0.0f);  // Sklonění obličeje dolů směrem k hráči (pitch)
        moon.object->transformation.rotate(90.0f, 0.0f, 1.0f, 0.0f);  // Otočení obličeje dopředu k hráči (+Z)
        moon.object->transformation.rotate(90.0f, 0.0f, 0.0f, 1.0f);  // Narovnání modelu (oči nahoře, pusa dole)
        moon.object->material.ambient = glm::vec3(0.5f);


        

        Material forestMaterial;
        forestMaterial.ambient = glm::vec3(0.002f);
        forestMaterial.specularStrength = 0.05f;

        DrawableObject& ground = addObject(DrawableObjectFactory::create(ObjectType::TexturedGround, groundProgram));
        ground.material = forestMaterial;
        ground.texture = grassTexture.getId();
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
            DrawableObject& bush = addObject(DrawableObjectFactory::create(ObjectType::Bush, bushProgram));
            bush.material = forestMaterial;
            bush.material.color = glm::vec3(0.27f, 0.70f, 0.12f);
            bush.transformation.translate(randomFloat(-10.0f, 10.0f), -1.5f, randomFloat(-25.0f, -2.0f));
            bush.transformation.scale(2.0f * randomFloat(0.9f, 1.1f));
        }

        for (int i = 0; i < FireFlyCount; i++)
        {
            Firefly& firefly = fireflies[i];
            firefly.center = glm::vec3(randomFloat(-8.0f, 8.0f), -0.2f, randomFloat(-23.5f, -3.5f));
            firefly.light = &addLight(Light::point(firefly.center, glm::vec3(1.0f, 0.85f, 0.3f), glm::vec3(1.0f, 0.3f, 0.4f)));

            firefly.object = &addObject(DrawableObjectFactory::create(ObjectType::Sphere, fireflyProgram));
            firefly.object->material.color = firefly.light->color;

            moveFirefly(i);
        }

        moon.light = &addLight(Light::directional(glm::vec3(0.0f, 20.0f, 10.0f), glm::vec3(0.1f)));


        flashlight = &addLight(Light::spot(
            getCamera()->getPosition(),         // poloha
            glm::vec3(0.0f, 0.0f, 0.0f),        // smer
            glm::vec3(1.0f),                    // barva a intenzita
            glm::vec3(1.0f, 0.09f, 0.032f),     // konstantni, linearni a kvadraticky utlum
            0.90, 0.95                          // aplha beta
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



        //Shrek jumpscare
        float dt = static_cast<float>(deltaTime);
        const glm::vec3& cameraPosition = getCamera()->getPosition();

        if (shrek == nullptr && !flashlightOn)
        {
            spawnTimer -= dt;

            if (spawnTimer <= 0.0f)
            {
                glm::vec3 forward = getCamera()->getDirection();
                forward.y = 0.0f;
                forward = glm::normalize(forward);

                shrekPosition = cameraPosition + forward * spawnDistance;
                shrekPosition.y = -1.5f; // Výška země v lese.

                shrek = &addObject(DrawableObjectFactory::create(ObjectType::Shrek, *shrekProgram));
                shrek->texture = shrekTexture.getId();
                shrek->transformation.translate(shrekPosition.x, shrekPosition.y, shrekPosition.z);
                shrek->transformation.scale(0.83f);

                spawnTimer = randomFloat(1.0f, 5.0f);
            }
        }

        if (shrek != nullptr)
        {
            glm::vec3 toPlayer = cameraPosition - shrekPosition;
            toPlayer.y = 0.0f;

            float distance = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z); // pythagorova veta
            if (distance > 1.0f)
            {
                float step = std::min(shrekSpeed * dt, distance - 1.0f);
                shrekPosition += (toPlayer / distance) * step;
                /*shrek->transformation.setPosition(shrekPosition);*/

                float angle = std::atan2(toPlayer.x, toPlayer.z) * 180.0f / 3.14159265f;

                shrek->transformation.clear();
                shrek->transformation.translate(shrekPosition.x, shrekPosition.y, shrekPosition.z);
                shrek->transformation.rotate(angle, 0.0f, 1.0f, 0.0f);
                shrek->transformation.scale(0.83f);
            }
        }
    }

    void onKeyPressed(int key) override
    {
        if (key == GLFW_KEY_F)
        {
            flashlightOn = !flashlightOn;

            if (flashlightOn == true)
            {
                flashlight->color = glm::vec3(0.9f);

                // Shrek jumpscare
                if (shrek != nullptr)
                {
                    glm::vec3 shrekCenter = shrekPosition + glm::vec3(0.0f, 0.75f, 0.0f);
                    glm::vec3 toShrek = glm::normalize(shrekCenter - getCamera()->getPosition());
                    float aim = glm::dot(getCamera()->getDirection(), toShrek);

                    if (aim > flashlight->alpha)
                    {
                        removeObject(shrek);
                        shrek = nullptr;
                    }
                }
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
        glm::vec3 center;
        Light* light;
        DrawableObject* object;
    };

    struct Moon
    {
        Light* light;
        DrawableObject* object;
    };
    Moon moon = {};

    static constexpr int FireFlyCount = 5;
    Firefly fireflies[FireFlyCount] = {};

    Light* flashlight = nullptr;

    Texture grassTexture{ "Textures/grass.png" };
    Texture shrekTexture{ "Textures/shrek.png" };
    Texture moonTexture{ "Textures/moon_00_0.png" };
    ShaderProgram* shrekProgram = nullptr;
    DrawableObject* shrek = nullptr;
    glm::vec3 shrekPosition{ 0.0f };

    float spawnTimer = randomFloat(1.0f, 5.0f);
    static constexpr float spawnDistance = 10.0f;
    static constexpr float shrekSpeed = 15.0f;
    

    float fireflyTime = 0.0f;
    bool flashlightOn = true;

    void moveFirefly(int i)
    {
        Firefly& firefly = fireflies[i];
        float t = fireflyTime * 0.7f + i * 3.14f;
        firefly.light->position = firefly.center + glm::vec3(2.0f * std::sin(t), 0.4f * std::sin(2.0f * t), 1.5f * std::cos(t));

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
