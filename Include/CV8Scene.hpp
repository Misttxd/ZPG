#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"
#include "Texture.h"

class CV8Scene : public Scene
{
public:
    CV8Scene() : Scene("CV8")
    {
        createCamera();

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
        //skybox.textureUnit = 4;
        skybox.alwaysOnTop = true;


        ShaderProgram& program = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        DrawableObject& ground = addObject(DrawableObjectFactory::create(ObjectType::TexturedGround, program));


        ground.transformation.translate(0.0f, -0.7f, 0.0f);
        ground.transformation.scale(2.0f);
        fenceTexture = loadTexture("textures/wooden_fence.png");
        ground.texture = fenceTexture;
        //ground.textureUnit = 0;

        DrawableObject& shrek = addObject(DrawableObjectFactory::create(ObjectType::Shrek, program));
        shrek.transformation.translate(-1.15f, -0.7f, 0.0f);
        shrek.transformation.scale(0.55f);
        shrekTexture = loadTexture("textures/shrek.png");
        shrek.texture = shrekTexture;
        //shrek.textureUnit = 1;

        DrawableObject& toiled = addObject(DrawableObjectFactory::create(ObjectType::Toiled, program));
        toiled.transformation.translate(0.0f, -0.7f, 0.0f);
        toiled.transformation.scale(0.48f);
        toiledTexture = loadTexture("textures/toiled.jpg");
        toiled.texture = toiledTexture;
        //toiled.textureUnit = 2;

        DrawableObject& fiona = addObject(DrawableObjectFactory::create(ObjectType::Fiona, program));
        fiona.transformation.translate(1.05f, -0.7f, 0.0f);
        fiona.transformation.scale(0.55f);
        fionaTexture = loadTexture("textures/fiona.png");
        fiona.texture = fionaTexture;
        //fiona.textureUnit = 3;
    }

    ~CV8Scene() override
    {
        glDeleteTextures(1, &fenceTexture);
        glDeleteTextures(1, &shrekTexture);
        glDeleteTextures(1, &toiledTexture);
        glDeleteTextures(1, &fionaTexture);
        glDeleteTextures(1, &skyboxTexture);
    }

private:
    GLuint fenceTexture = 0;
    GLuint shrekTexture = 0;
    GLuint toiledTexture = 0;
    GLuint fionaTexture = 0;
    GLuint skyboxTexture = 0;
};
