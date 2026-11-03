#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"


GLuint loadTexture(const char* path);
GLuint loadCubemap(const char* const (&paths)[6]);

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
        textures[4] = loadCubemap(skyPaths);
        skybox.texture = textures[4];
        skybox.textureTarget = GL_TEXTURE_CUBE_MAP;
        skybox.textureUnit = 4;
        skybox.alwaysOnTop = true;


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

    ~CV8Scene() override
    {
        glDeleteTextures(5, textures);
    }

private:
    GLuint textures[5] = {};
};
