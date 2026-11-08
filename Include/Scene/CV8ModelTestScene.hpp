#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"
#include "Texture.h"
#include "camera.h"

#include <array>

class CV8ModelTestScene : public Scene
{
public:
    CV8ModelTestScene() : Scene("CV8 - Model Test")
    {
        Camera& camera = createCamera();

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

        camera.move(-1.0f, 0.0f, 0.0f, 0.8 / 3.0);
        camera.move(0.0f, 1.0f, 0.0f, 1.25 / 3.0);
        camera.move(0.0f, 0.0f, 1.0f, 0.5);
        //camera.rotate(-1080.0f, 0.0f);

        ShaderProgram& program = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        DrawableObject& eb408 = addObject(DrawableObjectFactory::create(ObjectType::EB408, program));
        DrawableObject& door = addObject(DrawableObjectFactory::create(ObjectType::Door, program));
        DrawableObject& whiteboard = addObject(DrawableObjectFactory::create(ObjectType::Whiteboard, program));


        door.transformation.translate(-2.433f, 0.0055f, 7.747f);

        whiteboard.transformation.translate(-3.83f, 0.0f, 3.7f);
        whiteboard.transformation.rotate(-1.25f, 0.0f, 1.0f, 0.0f);

        eb408Texture = loadTexture("Textures/T_EB408.png");
        doorTexture = loadTexture("Textures/T_door_basecolor.png");
        whiteboardTexture = loadTexture("Textures/whiteboard_transformace.png");

        // Keep the matrix text legible when the board occupies fewer pixels on screen.
        glBindTexture(GL_TEXTURE_2D, whiteboardTexture);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5f);

        eb408.texture = eb408Texture;
        door.texture = doorTexture;
        whiteboard.texture = whiteboardTexture;

    }

    ~CV8ModelTestScene() override
    {
        glDeleteTextures(1, &eb408Texture);
        glDeleteTextures(1, &doorTexture);
        glDeleteTextures(1, &whiteboardTexture);

        glDeleteTextures(1, &skyboxTexture);
    }

private:
    GLuint eb408Texture = 0;
    GLuint doorTexture = 0;
    GLuint whiteboardTexture = 0;

    GLuint skyboxTexture = 0;
};
