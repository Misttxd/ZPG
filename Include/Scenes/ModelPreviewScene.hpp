#include "Scene.h"
#include "Texture.h"

#include "CV9Scene.hpp"

#include "../../Models/tree.h"
#include "../../Models/bushes.h"
#include "../../Models/TexturedModels/shrek.h"
#include "../../Models/TexturedModels/fiona.h"
#include "../../Models/TexturedModels/toiled.h"

class ModelPreviewScene : public Scene
{
public:
    ModelPreviewScene() : Scene("Preview")
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
        previewShrek->texture = shrekTexture.getId();

        previewFiona = createPreviewObject(fiona, sizeof(fiona), 8, texturedProgram, -0.8f, 0.9f);
        previewFiona->texture = fionaTexture.getId();

        previewToilet = createPreviewObject(toiled, sizeof(toiled), 8, texturedProgram, -0.8f, 0.48f);
        previewToilet->texture = toiletTexture.getId();

        treeShader.setLights(lights);
        bushShader.setLights(lights);
    }

    void drawModel(ObjectType type, double time)
    {
        switch (type)
        {
        case ObjectType::Tree:
            previewTree->draw(time);
            break;
        case ObjectType::Bush:
            previewBush->draw(time);
            break;
        case ObjectType::Shrek:
            previewShrek->draw(time);
            break;
        case ObjectType::Fiona:
            previewFiona->draw(time);
            break;
        case ObjectType::Toiled:
            previewToilet->draw(time);
            break;
        default:
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

    Texture shrekTexture{"Textures/shrek.png"};
    Texture fionaTexture{"Textures/fiona.png"};
    Texture toiletTexture{"Textures/toiled.jpg"};

    std::unique_ptr<DrawableObject> previewTree;
    std::unique_ptr<DrawableObject> previewBush;
    std::unique_ptr<DrawableObject> previewShrek;
    std::unique_ptr<DrawableObject> previewFiona;
    std::unique_ptr<DrawableObject> previewToilet;
};
