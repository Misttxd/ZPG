#pragma once

#include "Scene.h"
#include "SceneSignature.hpp"
#include "DrawableObjectFactory.h"
#include <cstdlib>


class LightingScene : public Scene
{
public:
	LightingScene() : Scene("Lighting")
	{
		createCamera();
		ShaderProgram& ball1Shader = addShaderProgram("shaders/light.vert", "shaders/light.frag");

		DrawableObject& ball1 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, ball1Shader));
		DrawableObject& ball2 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, ball1Shader));
		DrawableObject& ball3 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, ball1Shader));
		DrawableObject& ball4 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, ball1Shader));

		ball1Shader.setUniform("objectColor", 0.385f, 0.647f, 0.812f);
		ball1Shader.setUniform("lightPosition", 0.0f, 0.0f, 0.0f);

		ball1.transformation.translate(-0.9, 0, 0);
		ball1.transformation.scale(0.4);

		ball2.transformation.translate(0.9, 0, 0);
		ball2.transformation.scale(0.4);

		ball3.transformation.translate(0, 0.9, 0);
		ball3.transformation.scale(0.4);

		ball4.transformation.translate(0, -0.9, 0);
		ball4.transformation.scale(0.4);




	}

private:

};

