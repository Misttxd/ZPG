#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"

class PointLightScene : public Scene
{
public:
    PointLightScene() : Scene("Point light")
    {
        createCamera();
        ShaderProgram& program = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");

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

        addLight(Light::point(glm::vec3(0.0f, 1.5f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f, 0.05f, 0.01f)));

        addSignature(*this);
    }
};
