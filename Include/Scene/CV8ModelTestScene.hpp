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
        // Start inside the room with both the doorway and the board in view.
        camera.move(-1.0f, 0.0f, 0.0f, 0.8 / 3.0);
        camera.move(0.0f, 1.0f, 0.0f, 1.25 / 3.0);
        camera.move(0.0f, 0.0f, 1.0f, 0.5);
        camera.rotate(-1080.0f, 0.0f);

        ShaderProgram& program = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");
        DrawableObject& room = addObject(DrawableObjectFactory::create(ObjectType::EB408, program));
        DrawableObject& door = addObject(DrawableObjectFactory::create(ObjectType::Door, program));
        DrawableObject& whiteboard = addObject(DrawableObjectFactory::create(ObjectType::Whiteboard, program));

        // The door's origin is at the right jamb, with its frame extending toward -Z.
        door.transformation.translate(-2.433f, 0.0055f, 7.747f);
        // Match the slight angle of the solid wall opposite the windows.
        whiteboard.transformation.translate(-3.83f, 0.0f, 3.7f);
        whiteboard.transformation.rotate(-1.25f, 0.0f, 1.0f, 0.0f);

        try
        {
            room.texture = textures[0] = loadTexture("Textures/T_EB408.png");
            door.texture = textures[1] = loadTexture("Textures/T_door_basecolor.png");
            whiteboard.texture = textures[2] = loadTexture("Textures/T_Whiteboard_BaseColor.png");
        }
        catch (...)
        {
            glDeleteTextures(static_cast<GLsizei>(textures.size()), textures.data());
            throw;
        }
    }

    ~CV8ModelTestScene() override
    {
        glDeleteTextures(static_cast<GLsizei>(textures.size()), textures.data());
    }

private:
    std::array<GLuint, 3> textures{};
};
