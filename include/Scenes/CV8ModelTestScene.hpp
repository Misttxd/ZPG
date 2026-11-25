#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"
#include "Texture.h"
#include "camera.h"

#include <array>

class CV8ModelTestScene : public Scene
{
public:
    CV8ModelTestScene() : Scene("CV8")
    {
        Camera& camera = createCamera();

        ShaderProgram& skyProgram = addShaderProgram("shaders/skybox.vert", "shaders/skybox.frag");
        DrawableObject& skybox = addObject(DrawableObjectFactory::create(ObjectType::Skybox, skyProgram));

        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        skybox.texture = skyboxTexture.getId();
        skybox.textureTarget = GL_TEXTURE_CUBE_MAP;
        //skybox.textureUnit = 4;
        skybox.alwaysOnTop = true;

        camera.move(-1.0f, 0.0f, 0.0f, 0.8 / 3.0);
        camera.move(0.0f, 1.0f, 0.0f, 1.85 / 3.0);
        camera.move(0.0f, 0.0f, 1.0f, 0.5);
        camera.rotate(-900.0f, 55.0f);

        ShaderProgram& program = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        DrawableObject& eb408 = addObject(DrawableObjectFactory::create(ObjectType::EB408, program));
        DrawableObject& door = addObject(DrawableObjectFactory::create(ObjectType::Door, program));
        DrawableObject& whiteboard = addObject(DrawableObjectFactory::create(ObjectType::Whiteboard, program));


        door.transformation.translate(-2.433f, 0.0055f, 7.747f);

        whiteboard.transformation.translate(-3.83f, 0.0f, 3.7f);
        whiteboard.transformation.rotate(-1.25f, 0.0f, 1.0f, 0.0f);



        eb408.texture = eb408Texture.getId();
        door.texture = doorTexture.getId();
        whiteboard.texture = whiteboardTexture.getId();

        DrawableObject& shrek = addObject(DrawableObjectFactory::create(ObjectType::Shrek, program));
        DrawableObject& fiona = addObject(DrawableObjectFactory::create(ObjectType::Fiona, program));

        shrek.texture = shrekTexture.getId();
        fiona.texture = fionaTexture.getId();

        shrek.transformation.translate(-3.08f, 0.01f, 5.98f);
        shrek.transformation.rotate(90.0f, 0.0f, 1.0f, 0.0f);
        shrek.transformation.scale(0.83f);

        fiona.transformation.translate(-3.08f, 0.01f, 1.60f);
        fiona.transformation.rotate(90.0f, 0.0f, 1.0f, 0.0f);
        fiona.transformation.scale(0.83f);
    }

private:
    Texture eb408Texture{"Textures/T_EB408.png"};
    Texture doorTexture{"Textures/T_door_basecolor.png"};
    Texture whiteboardTexture{"Textures/whiteboard_transformace.png"};
    Texture shrekTexture{"Textures/shrek.png"};
    Texture fionaTexture{"Textures/fiona.png"};

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
