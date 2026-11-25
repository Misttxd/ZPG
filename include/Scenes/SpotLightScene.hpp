#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"

class SpotLightScene : public Scene
{
public:
    SpotLightScene() : Scene("Spotlight")
    {
        createCamera();
        ShaderProgram& program = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        ShaderProgram& fireflyProgram = addShaderProgram("shaders/lighting.vert", "shaders/ambient.frag");

        Material material;
        material.color = glm::vec3(0.385f, 0.647f, 0.812f);
        material.ambient = material.color * 0.03f;
        material.specularStrength = 0.5f;
        material.shininess = 32.0f;

        const glm::vec3 positions[] = {
            glm::vec3(-0.8f, 0.0f, -1.0f),
            glm::vec3(0.8f, 0.0f, -1.0f),
            glm::vec3(0.0f, 0.85f, -1.0f),
            glm::vec3(0.0f, -0.85f, -0.3f)
        };

        for (const glm::vec3& position : positions)
        {
            DrawableObject& ball = addObject(DrawableObjectFactory::create(ObjectType::Sphere, program));
            ball.material = material;
            ball.transformation.translate(position.x, position.y, position.z);
            ball.transformation.scale(0.35f);
        }

        DrawableObject& ground = addObject(DrawableObjectFactory::create(ObjectType::Ground, program));
        ground.material = material;
        ground.transformation.translate(0.0f, -1.2f, -1.0f);
        ground.transformation.scale(3.0f);

        addLight(Light::spot(glm::vec3(0.0f, 2.0f, 2.0f), glm::vec3(0.0f, -2.85f, -2.3f), glm::vec3(1.0f), glm::vec3(1.0f, 0.05f, 0.01f) , 0.9, 0.95));


        DrawableObject &object = addObject(DrawableObjectFactory::create(ObjectType::Sphere, fireflyProgram));

        object.material.color = glm::vec3(1.0f, 0.0f, 0.0f);

        object.transformation.translate(0.0f, 2.0f, 2.0f);
        object.transformation.scale(0.2);


          
        addSignature(*this);
    }
};
