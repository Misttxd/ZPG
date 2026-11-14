#pragma once

#include "../Scene.h"
#include "DrawableObjectFactory.h"
#include "Texture.h"

class FionaScene : public Scene
{
public:
    FionaScene() : Scene("Fiona")
    {
        createCamera();

        ShaderProgram& program = addShaderProgram("shaders/texture.vert", "shaders/texture.frag");

        DrawableObject& fiona = addObject(DrawableObjectFactory::create(ObjectType::Fiona, program));

        fiona.transformation.translate(0.0f, -0.5f, 0.0f);
        // fiona.transformation.scale(0.55f);
        fiona.transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, 45.0f);


        fiona.texture = fionaTexture.getId();
        //fiona.textureUnit = 3;
    }

private:
    Texture fionaTexture{"textures/fiona.png"};
};
