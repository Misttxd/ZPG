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

        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        skybox.texture = skyboxTexture.getId();
        skybox.textureTarget = GL_TEXTURE_CUBE_MAP;
        //skybox.textureUnit = 4;
        skybox.alwaysOnTop = true;


        ShaderProgram& program = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        DrawableObject& ground = addObject(DrawableObjectFactory::create(ObjectType::TexturedGround, program));


        ground.transformation.translate(0.0f, -0.7f, 0.0f);
        ground.transformation.scale(2.0f);
        ground.texture = fenceTexture.getId();
        //ground.textureUnit = 0;

        DrawableObject& shrek = addObject(DrawableObjectFactory::create(ObjectType::Shrek, program));
        shrek.transformation.translate(-1.15f, -0.7f, 0.0f);
        shrek.transformation.scale(0.55f);
        shrek.texture = shrekTexture.getId();
        //shrek.textureUnit = 1;

        DrawableObject& toiled = addObject(DrawableObjectFactory::create(ObjectType::Toiled, program));
        toiled.transformation.translate(0.0f, -0.7f, 0.0f);
        toiled.transformation.scale(0.48f);
        toiled.texture = toiledTexture.getId();
        //toiled.textureUnit = 2;

        DrawableObject& fiona = addObject(DrawableObjectFactory::create(ObjectType::Fiona, program));

        fiona.transformation.translate(1.05f, -0.7f, 0.0f);
        fiona.transformation.scale(0.55f);
        fiona.transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, 45.0f);


        fiona.texture = fionaTexture.getId();
        //fiona.textureUnit = 3;
    }

private:
    Texture fenceTexture{"textures/wooden_fence.png"};
    Texture shrekTexture{"textures/shrek.png"};
    Texture toiledTexture{"textures/toiled.jpg"};
    Texture fionaTexture{"textures/fiona.png"};
    const char* skyPaths[6] = {
        "Textures/skybox/right.jpg",
        "Textures/skybox/left.jpg",
        "Textures/skybox/top.jpg",
        "Textures/skybox/bottom.jpg",
        "Textures/skybox/front.jpg",
        "Textures/skybox/back.jpg"
    };
    Texture skyboxTexture{skyPaths};
};
