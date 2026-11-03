#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"


GLuint loadTexture(const char* path);


class CV8SkydomeScene : public Scene
{
public:
    CV8SkydomeScene() : Scene("CV8 - Skydome")
    {
        createCamera();

        ShaderProgram& skyProgram = addShaderProgram("shaders/skybox.vert", "shaders/skydome.frag");
        DrawableObject& dome = addObject(DrawableObjectFactory::create(ObjectType::Sphere, skyProgram));
        textures[4] = loadTexture("Textures/skydome.jpg");
        dome.texture = textures[4];
        dome.textureUnit = 4;
        dome.alwaysOnTop = true;

        ShaderProgram& program = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        DrawableObject& ground = addObject(DrawableObjectFactory::create(ObjectType::TexturedGround, program));


        ground.transformation.translate(0.0f, -0.7f, 0.0f);
        ground.transformation.scale(2.0f);
        textures[0] = loadTexture("textures/wooden_fence.png");
        ground.texture = textures[0];
        ground.textureUnit = 0;

        DrawableObject& shrek = addObject(DrawableObjectFactory::create(ObjectType::Shrek, program));
        shrek.transformation.translate(-1.15f, -0.7f, 0.0f);
        shrek.transformation.scale(0.55f);
        textures[1] = loadTexture("textures/shrek.png");
        shrek.texture = textures[1];
        shrek.textureUnit = 1;

        DrawableObject& toiled = addObject(DrawableObjectFactory::create(ObjectType::Toiled, program));
        toiled.transformation.translate(0.0f, -0.7f, 0.0f);
        toiled.transformation.scale(0.48f);
        textures[2] = loadTexture("textures/toiled.jpg");
        toiled.texture = textures[2];
        toiled.textureUnit = 2;

        DrawableObject& fiona = addObject(DrawableObjectFactory::create(ObjectType::Fiona, program));
        fiona.transformation.translate(1.05f, -0.7f, 0.0f);
        fiona.transformation.scale(0.55f);
        textures[3] = loadTexture("textures/fiona.png");
        fiona.texture = textures[3];
        fiona.textureUnit = 3;
    }

    ~CV8SkydomeScene() override
    {
        glDeleteTextures(5, textures);
    }

private:
    GLuint textures[5] = {};
};
