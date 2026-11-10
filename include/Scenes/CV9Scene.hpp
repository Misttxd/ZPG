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
#include <cstdlib>

enum PreviewModel
{
    TreeModel,
    BushModel,
    ShrekModel,
    FionaModel,
    ToiletModel,
    ModelCount
};

class CV9Scene : public Scene
{
public:
    CV9Scene() : Scene("CV9 - Teren")
    {
        Camera& camera = createCamera();
        camera.move(-1.0f, 0.0f, 0.0f, 10.0 / 3.0);
        camera.move(0.0f, 0.0f, 1.0f, 3.8 / 3.0);
        camera.rotate(0.0f, 130.0f);

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

        ShaderProgram& terrainProgram = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        DrawableObject& terrain = addObject(DrawableObjectFactory::create(ObjectType::Terrain, terrainProgram));
        terrainId = terrain.getId();
        grassTexture = loadTexture("Textures/grass.png");
        terrain.texture = grassTexture;
        terrain.transformation.scale(0.30f);

        treeProgram = &addShaderProgram("shaders/forestLighting.vert", "shaders/forestLighting.frag");
        bushProgram = &addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        texturedModelProgram = &addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        shrekTexture = loadTexture("Textures/shrek.png");
        fionaTexture = loadTexture("Textures/fiona.png");
        toiletTexture = loadTexture("Textures/toiled.jpg");
        addLight().position = glm::vec3(-10.0f, 25.0f, 10.0f);
        Light& fillLight = addLight();
        fillLight.position = glm::vec3(10.0f, 6.0f, -15.0f);
        fillLight.color = glm::vec3(0.5f);

        // The valley floor is flat at y = 0 within these bounds.
        const int treeCount = 12;
        for (int i = 0; i < treeCount; ++i)
        {
           glm::vec3 pos = glm::vec3(randomFloat(-8.0f, 8.0f), 0.0f, randomFloat(-8.0f, 5.0f));

            DrawableObject& tree = addObject(DrawableObjectFactory::create(ObjectType::Tree, *treeProgram));
            tree.material.ambient = glm::vec3(0.08f);
            tree.material.specularStrength = 0.05f;
            tree.transformation.translate(pos.x, pos.y, pos.z);
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

    int getSelectedModel() const { return selectedModel; }

private:
    void onKeyPressed(int key) override
    {
        if (key == GLFW_KEY_M)
            selectedModel = (selectedModel + 1) % ModelCount;
    }

    void onWorldClick(GLuint index, const glm::vec3& pos) override
    {
        if (index != terrainId)
            return;

        switch (selectedModel)
        {
        case TreeModel:
            addTree(pos);
            break;
        case BushModel:
        {
            DrawableObject& bush = addObject(DrawableObjectFactory::create(ObjectType::Bush, *bushProgram));
            bush.material.color = glm::vec3(0.27f, 0.70f, 0.12f);
            bush.transformation.translate(pos.x, pos.y, pos.z);
            bush.transformation.scale(2.0f);
            break;
        }
        case ShrekModel:
            addTexturedModel(ObjectType::Shrek, shrekTexture, pos, 0.83f);
            break;
        case FionaModel:
            addTexturedModel(ObjectType::Fiona, fionaTexture, pos, 0.83f);
            break;
        case ToiletModel:
            addTexturedModel(ObjectType::Toiled, toiletTexture, pos, 0.48f);
            break;
        }
    }
    bool wantsPreviewWindow() const override
    {
        return dualWindow;
    }

    static float randomFloat(float min, float max)
    {
        return min + (max - min) * (static_cast<float>(std::rand()) / RAND_MAX);
    }

    void addTree(const glm::vec3& pos)
    {
        DrawableObject& tree = addObject(DrawableObjectFactory::create(ObjectType::Tree, *treeProgram));
        tree.material.ambient = glm::vec3(0.08f);
        tree.material.specularStrength = 0.05f;
        tree.transformation.translate(pos.x, pos.y, pos.z);
        tree.transformation.rotate(randomFloat(0.0f, 360.0f), 0.0f, 1.0f, 0.0f);
        tree.transformation.scale(0.42f * randomFloat(0.6f, 1.2f));
    }

    void addTexturedModel(ObjectType type, GLuint texture, const glm::vec3& pos, float scale)
    {
        DrawableObject& object = addObject(DrawableObjectFactory::create(type, *texturedModelProgram));
        object.texture = texture;
        object.transformation.translate(pos.x, pos.y, pos.z);
        object.transformation.scale(scale);
    }

    bool dualWindow = 1;
    int selectedModel = TreeModel;
    GLuint terrainId = 0;

    ShaderProgram* treeProgram = nullptr;
    ShaderProgram* bushProgram = nullptr;
    ShaderProgram* texturedModelProgram = nullptr;

    GLuint grassTexture = 0;
    GLuint skyboxTexture = 0;
    GLuint shrekTexture = 0;
    GLuint fionaTexture = 0;
    GLuint toiletTexture = 0;
};

class ModelPreviewScene : public Scene
{
public:
    ModelPreviewScene() : Scene("Nahled modelu")
    {
        createCamera();
        ShaderProgram& treeShader = addShaderProgram("shaders/forestLighting.vert", "shaders/forestLighting.frag");
        ShaderProgram& bushShader = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
        addLight().position = glm::vec3(2.0f, 4.0f, 3.0f);

        previewTree = createPreviewObject(tree, sizeof(tree), 6, treeShader, -1.25f, 0.33f);
        previewTree->material.ambient = glm::vec3(0.12f);

        previewBush = createPreviewObject(bushes, sizeof(bushes), 6, bushShader, -0.5f, 2.5f);
        previewBush->material.color = glm::vec3(0.27f, 0.70f, 0.12f);

        ShaderProgram& texturedProgram = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        previewShrek = createPreviewObject(shrek, sizeof(shrek), 8, texturedProgram, -0.8f, 0.85f);
        previewShrek->texture = loadTexture("Textures/shrek.png");

        previewFiona = createPreviewObject(fiona, sizeof(fiona), 8, texturedProgram, -0.8f, 0.9f);
        previewFiona->texture = loadTexture("Textures/fiona.png");

        previewToilet = createPreviewObject(toiled, sizeof(toiled), 8, texturedProgram, -0.8f, 0.48f);
        previewToilet->texture = loadTexture("Textures/toiled.jpg");

        Scene::Draw(); // Upload the fixed preview light to the shaders.
    }

    ~ModelPreviewScene() override
    {
        glDeleteTextures(1, &previewShrek->texture);
        glDeleteTextures(1, &previewFiona->texture);
        glDeleteTextures(1, &previewToilet->texture);
    }

    void drawModel(int index, double time)
    {
        switch (index)
        {
        case TreeModel:
            previewTree->draw(time);
            break;
        case BushModel:
            previewBush->draw(time);
            break;
        case ShrekModel:
            previewShrek->draw(time);
            break;
        case FionaModel:
            previewFiona->draw(time);
            break;
        case ToiletModel:
            previewToilet->draw(time);
            break;
        }
    }

private:
    static std::unique_ptr<DrawableObject> createPreviewObject(
        const float* vertices, int size, int floatsPerVertex, ShaderProgram& program, float y, float scale)
    {
        auto model = std::make_shared<Model>();
        model->create(vertices, size, floatsPerVertex);
        auto object = std::make_unique<DrawableObject>(model, program);
        object->transformation.translate(0.0f, y, 0.0f);
        object->transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, 35.0f);
        object->transformation.scale(scale);
        return object;
    }

    std::unique_ptr<DrawableObject> previewTree;
    std::unique_ptr<DrawableObject> previewBush;
    std::unique_ptr<DrawableObject> previewShrek;
    std::unique_ptr<DrawableObject> previewFiona;
    std::unique_ptr<DrawableObject> previewToilet;
};
