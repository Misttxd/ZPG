#include "DrawableObjectFactory.h"
#include "Model.h"
#include "../Models/sphere.h"
#include "../Models/sun.h"
#include "../Models/earth.h"
#include "../Models/moon.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"
#include "../Models/plain.h"
#include "../Models/BRU0098.h"
#include "../Models/clock.h"
#include "../Models/rocket.h"
#include <map>
#include <stdexcept>

std::unique_ptr<DrawableObject> DrawableObjectFactory::create(ObjectType type, ShaderProgram& shaderProgram)
{

    static std::map<ObjectType, std::weak_ptr<Model>> models;
    std::shared_ptr<Model> model;
    auto found = models.find(type);
    if (found != models.end())
    {
        model = found->second.lock();
    }

    if (!model)
    {
        const float triangle[] = {
            -0.5f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
        };
        const float* vertices;
        int dataSize;
        int floatsPerVertex = 6;

        switch (type)
        {
        case ObjectType::Triangle:
            vertices = triangle;
            dataSize = sizeof(triangle);
            break;
        case ObjectType::Sphere:
            vertices = sphere;
            dataSize = sizeof(sphere);
            break;
        case ObjectType::Sun:
            vertices = sun;
            dataSize = sizeof(sun);
            floatsPerVertex = 9;
            break;
        case ObjectType::Earth:
            vertices = earth;
            dataSize = sizeof(earth);
            floatsPerVertex = 9;
            break;
        case ObjectType::Moon:
            vertices = moon;
            dataSize = sizeof(moon);
            floatsPerVertex = 9;
            break;
        case ObjectType::Tree:
            vertices = tree;
            dataSize = sizeof(tree);
            break;
        case ObjectType::Bush:
            vertices = bushes;
            dataSize = sizeof(bushes);
            break;
        case ObjectType::Ground:
            vertices = plain;
            dataSize = sizeof(plain);
            break;
        case ObjectType::Login:
            vertices = bru0098;
            dataSize = sizeof(bru0098);
            break;
        case ObjectType::Clock:
            vertices = clockModel;
            dataSize = sizeof(clockModel);
            floatsPerVertex = 9;
            break;
        case ObjectType::Rocket:
            vertices = rocket;
            dataSize = sizeof(rocket);
            floatsPerVertex = 9;
            break;
        default:
            throw std::invalid_argument("Unknown object type.");
        }

        model = std::make_shared<Model>();
        model->create(vertices, dataSize, floatsPerVertex);
        models[type] = model;
    }

    return std::make_unique<DrawableObject>(model, shaderProgram);
}
