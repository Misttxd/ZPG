#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"

#include "Texture.h"


class CV8SkydomeScene : public Scene
{
public:
    CV8SkydomeScene() : Scene("CV8 - Skydome")
    {
        createCamera();

        ShaderProgram& skyProgram = addShaderProgram("shaders/skybox.vert", "shaders/skydome.frag");
        DrawableObject& dome = addObject(DrawableObjectFactory::create(ObjectType::Sphere, skyProgram));

        skydomeTexture = loadTexture("Textures/skydome.jpg");
        dome.texture = skydomeTexture;

        dome.alwaysOnTop = true;

        ShaderProgram& program = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        DrawableObject& ground = addObject(DrawableObjectFactory::create(ObjectType::TexturedGround, program));


        ground.transformation.translate(0.0f, -0.7f, 0.0f);
        ground.transformation.scale(2.0f);

        fenceTexture = loadTexture("textures/wooden_fence.png");
        ground.texture = fenceTexture;


        DrawableObject& shrek = addObject(DrawableObjectFactory::create(ObjectType::Shrek, program));
        shrek.transformation.translate(-1.15f, -0.7f, 0.0f);
        shrek.transformation.scale(0.55f);

        shrekTexture = loadTexture("textures/shrek.png");
        shrek.texture = shrekTexture;


        DrawableObject& toiled = addObject(DrawableObjectFactory::create(ObjectType::Toiled, program));
        toiled.transformation.translate(0.0f, -0.7f, 0.0f);
        toiled.transformation.scale(0.48f);

        toiledTexture = loadTexture("textures/toiled.jpg");
        toiled.texture = toiledTexture;


        DrawableObject& fiona = addObject(DrawableObjectFactory::create(ObjectType::Fiona, program));
        fiona.transformation.translate(1.05f, -0.7f, 0.0f);
        fiona.transformation.scale(0.55f);

        fionaTexture = loadTexture("textures/fiona.png");
        fiona.texture = fionaTexture;

    }

    ~CV8SkydomeScene() override
    {
        //glDeleteTextures(5, textures);
        glDeleteTextures(1, &skydomeTexture);
        glDeleteTextures(1, &fenceTexture);
        glDeleteTextures(1, &shrekTexture);
        glDeleteTextures(1, &fionaTexture);
        glDeleteTextures(1, &toiledTexture);
    }

private:
    /*GLuint textures[5] = {};*/
    
    GLuint skydomeTexture = 0;
    GLuint fenceTexture = 0;
    GLuint shrekTexture = 0;
    GLuint fionaTexture = 0;
    GLuint toiledTexture = 0;
};
