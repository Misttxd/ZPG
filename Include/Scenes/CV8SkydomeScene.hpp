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

        dome.texture = skydomeTexture.getId();

        dome.alwaysOnTop = true;

        ShaderProgram& program = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        DrawableObject& ground = addObject(DrawableObjectFactory::create(ObjectType::TexturedGround, program));


        ground.transformation.translate(0.0f, -0.7f, 0.0f);
        ground.transformation.scale(2.0f);

        ground.texture = fenceTexture.getId();


        DrawableObject& shrek = addObject(DrawableObjectFactory::create(ObjectType::Shrek, program));
        shrek.transformation.translate(-1.15f, -0.7f, 0.0f);
        shrek.transformation.scale(0.55f);

        shrek.texture = shrekTexture.getId();


        DrawableObject& toiled = addObject(DrawableObjectFactory::create(ObjectType::Toiled, program));
        toiled.transformation.translate(0.0f, -0.7f, 0.0f);
        toiled.transformation.scale(0.48f);

        toiled.texture = toiledTexture.getId();


        DrawableObject& fiona = addObject(DrawableObjectFactory::create(ObjectType::Fiona, program));
        fiona.transformation.translate(1.05f, -0.7f, 0.0f);
        fiona.transformation.scale(0.55f);

        fiona.texture = fionaTexture.getId();

    }

private:
    /*GLuint textures[5] = {};*/
    
    Texture skydomeTexture{"Textures/skydome.jpg"};
    Texture fenceTexture{"textures/wooden_fence.png"};
    Texture shrekTexture{"textures/shrek.png"};
    Texture fionaTexture{"textures/fiona.png"};
    Texture toiledTexture{"textures/toiled.jpg"};
};
