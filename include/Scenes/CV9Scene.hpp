#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"
#include "Texture.h"
#include "camera.h"
#include "Model.h"
#include "../../Models/tree.h"
#include "../../Models/bushes.h"
#include "../../Models/TexturedModels/shrek.h"
#include "../../Models/TexturedModels/fiona.h"
#include "../../Models/TexturedModels/toiled.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <map>

class CV9Scene : public Scene
{
public:
    CV9Scene() : Scene("CV9")
    {
        // Camera
        Camera& camera = createCamera();
        camera.move(-1.0f, 0.0f, 0.0f, 10.0 / 3.0);
        camera.move(0.0f, 0.0f, 1.0f, 3.8 / 3.0);
        camera.rotate(0.0f, 130.0f);

        // Skybox
        ShaderProgram& skyProgram = addShaderProgram("shaders/skybox.vert", "shaders/skybox.frag");
        DrawableObject& skybox = addObject(DrawableObjectFactory::create(ObjectType::Skybox, skyProgram));
        const char* skyPaths[6] = {
            "Textures/skybox/right.jpg",
            "Textures/skybox/left.jpg",
            "Textures/skybox/top.jpg",
            "Textures/skybox/bottom.jpg",
            "Textures/skybox/front.jpg",
            "Textures/skybox/back.jpg"
        };

        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        skyboxTexture = loadCubemap(skyPaths);
        skybox.texture = skyboxTexture;
        skybox.textureTarget = GL_TEXTURE_CUBE_MAP;
        skybox.alwaysOnTop = true;
        skybox.setId(0);

        // Terrain
        ShaderProgram& terrainProgram = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        DrawableObject& terrain = addObject(DrawableObjectFactory::create(ObjectType::Terrain, terrainProgram));
        terrainId = terrain.getId();
        grassTexture = loadTexture("Textures/grass.png");
        terrain.texture = grassTexture;
        terrain.transformation.scale(0.30f);

        // Models for placement and selection
        treeProgram = &addShaderProgram("shaders/forestLighting.vert", "shaders/forestLighting.frag");
        bushProgram = &addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        texturedModelProgram = &addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        outlineProgram = &addShaderProgram("shaders/lighting.vert", "shaders/ambient.frag");
        shrekTexture = loadTexture("Textures/shrek.png");
        fionaTexture = loadTexture("Textures/fiona.png");
        toiletTexture = loadTexture("Textures/toiled.jpg");

        // Daylight
        addLight().position = glm::vec3(-10.0f, 25.0f, 10.0f);
        Light& fillLight = addLight();
        fillLight.position = glm::vec3(10.0f, 6.0f, -15.0f);
        fillLight.color = glm::vec3(0.5f);

       
        const int treeCount = 12;
        for (int i = 0; i < treeCount; i++)
        {
            DrawableObject& tree = addObject(DrawableObjectFactory::create(ObjectType::Tree, *treeProgram));
            tree.material.ambient = glm::vec3(0.08f);
            tree.material.specularStrength = 0.05f;
            tree.transformation.translate(randomFloat(-8.0f, 8.0f), 0.0f, randomFloat(-8.0f, 5.0f));
            tree.transformation.rotate(randomFloat(0.0f, 360.0f), 0.0f, 1.0f, 0.0f);
            tree.transformation.scale(0.42f * randomFloat(0.6f, 1.2f));
        }
    }

    ~CV9Scene() override
    {
        glDeleteTextures(1, &grassTexture);
        glDeleteTextures(1, &skyboxTexture);
        glDeleteTextures(1, &shrekTexture);
        glDeleteTextures(1, &fionaTexture);
        glDeleteTextures(1, &toiletTexture);
    }

    void update(double deltaTime, float clockTime) override
    {
        Scene::update(deltaTime, clockTime);
        for (auto& [object, route] : routes)
        {
            route.phase = std::fmod(route.phase + deltaTime / 3.0, 2.0);
            float t = static_cast<float>(route.phase);
            if (t > 1.0f)
                t = 2.0f - t;

            object->positionOffset = route.startOffset + t * route.delta;
        }
    }

    void Draw() override
    {
        Scene::Draw();
        if (!outlinedObject)
        {
            return;
        }

        glStencilFunc(GL_NOTEQUAL, outlinedObject->getId(), 0xFF);
        glStencilMask(0);
        glDepthMask(GL_FALSE);
        
        outlinedObject->drawOutline(*outlineProgram, elapsedTime);

        glDepthMask(GL_TRUE);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
    }

    ObjectType getPreviewModel() const
    {
        if (outlinedObject)
        {
            return outlinedObject->type;
        }
        else
        {
            return modelToPlace;
        }
    }

    bool wantsPreviewWindow() const override
    {
        return dualWindow;
    }

private:
    enum class Mode { Place, Route };

    struct Route
    {
        glm::vec3 startOffset;
        glm::vec3 delta;
        double phase = 0.0;
    };

    static float randomFloat(float min, float max)
    {
        return min + (max - min) * (static_cast<float>(std::rand()) / RAND_MAX);
    }

    void onKeyPressed(int key) override
    {
        if (key == GLFW_KEY_M)
        {
            switch (modelToPlace)
            {
            case ObjectType::Tree:
                modelToPlace = ObjectType::Bush;
                break;
            case ObjectType::Bush:
                modelToPlace = ObjectType::Shrek;
                break;
            case ObjectType::Shrek:
                modelToPlace = ObjectType::Fiona;
                break;
            case ObjectType::Fiona:
                modelToPlace = ObjectType::Toiled;
                break;
            default:
                modelToPlace = ObjectType::Tree;
                break;
            }
            outlinedObject = nullptr;
            hasRouteStart = false;
        }

        if (key != GLFW_KEY_P)
            return;

        hasRouteStart = false;
        switch (mode)
        {
        case Mode::Place:
            mode = Mode::Route;
            std::puts("Trasa: klikni na zacatek a konec.");
            break;
        case Mode::Route:
            mode = Mode::Place;
            std::puts("Vkladani: klikni na teren.");
            break;
        }
    }

    void onWorldClick(GLuint index, const glm::vec3& pos) override
    {
        if (index == 0)
            return;

        if (index != terrainId) //not able to place out of terrain
        {
            DrawableObject* object = findObject(index);
            hasRouteStart = false;

            if (routes.erase(object) > 0)
            {
                if (outlinedObject == object)
                    outlinedObject = nullptr;

                removeObject(object);
            }
            else
            {
                outlinedObject = object;
            }

            return;
        }

        if (mode == Mode::Place)
        {
            outlinedObject = nullptr;
            addSelectedModel(pos);
            return;
        }

        if (!hasRouteStart)
        {
            routeStart = pos;
            hasRouteStart = true;
            std::puts("Trasa: klikni na konec.");
            return;
        }

        if (glm::length(pos - routeStart) < 0.01f)
            return;

        DrawableObject* object = outlinedObject;
        if (!object)
            object = &addSelectedModel(routeStart);

        glm::vec3 originalPosition(object->transformation.getMatrix(elapsedTime)[3]);
        glm::vec3 startOffset = routeStart - originalPosition;
        routes[object] = {startOffset, pos - routeStart};
        object->positionOffset = startOffset;
        hasRouteStart = false;
        std::puts("Trasa hotova. Vyber dalsi model a klikni na zacatek a konec. P prepne na vkladani.");
    }

    DrawableObject& addSelectedModel(const glm::vec3& pos)
    {
        switch (modelToPlace)
        {
        case ObjectType::Tree:
        {
            DrawableObject& tree = addObject(DrawableObjectFactory::create(ObjectType::Tree, *treeProgram));
            tree.material.ambient = glm::vec3(0.08f);
            tree.material.specularStrength = 0.05f;
            tree.transformation.translate(pos.x, pos.y, pos.z);
            tree.transformation.rotate(randomFloat(0.0f, 360.0f), 0.0f, 1.0f, 0.0f);
            tree.transformation.scale(0.42f * randomFloat(0.6f, 1.2f));
            return tree;
        }

        case ObjectType::Bush:
        {
            DrawableObject& bush = addObject(DrawableObjectFactory::create(ObjectType::Bush, *bushProgram));
            bush.material.color = glm::vec3(0.27f, 0.70f, 0.12f);
            bush.transformation.translate(pos.x, pos.y, pos.z);
            bush.transformation.scale(2.0f);
            return bush;
        }
        case ObjectType::Shrek:
            return addTexturedModel(ObjectType::Shrek, shrekTexture, pos, 0.83f);

        case ObjectType::Fiona:
            return addTexturedModel(ObjectType::Fiona, fionaTexture, pos, 0.83f);
        default:
            return addTexturedModel(ObjectType::Toiled, toiletTexture, pos, 0.48f);
        }
    }
    

    DrawableObject& addTexturedModel(ObjectType type, GLuint texture, const glm::vec3& pos, float scale)
    {
        DrawableObject& object = addObject(DrawableObjectFactory::create(type, *texturedModelProgram));
        object.texture = texture;
        object.transformation.translate(pos.x, pos.y, pos.z);
        object.transformation.scale(scale);
        return object;
    }

    bool dualWindow = 1;
    ObjectType modelToPlace = ObjectType::Tree;
    GLuint terrainId = 0;

    Mode mode = Mode::Place;
    bool hasRouteStart = false;
    glm::vec3 routeStart{0.0f};
    std::map<DrawableObject*, Route> routes;
    DrawableObject* outlinedObject = nullptr;

    ShaderProgram* treeProgram = nullptr;
    ShaderProgram* bushProgram = nullptr;
    ShaderProgram* texturedModelProgram = nullptr;
    ShaderProgram* outlineProgram = nullptr;

    GLuint grassTexture = 0;
    GLuint skyboxTexture = 0;
    GLuint shrekTexture = 0;
    GLuint fionaTexture = 0;
    GLuint toiletTexture = 0;
};