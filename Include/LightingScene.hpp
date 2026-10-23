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
		ShaderProgram& ambientProgram = addShaderProgram("shaders/lighting.vert", "shaders/ambient.frag");
		ShaderProgram& lambertProgram = addShaderProgram("shaders/lighting.vert", "shaders/lambert.frag");
		ShaderProgram& phongProgram = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
		ShaderProgram& blinnProgram = addShaderProgram("shaders/lighting.vert", "shaders/blinnPhong.frag");

		DrawableObject& ball1 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, ambientProgram));
		DrawableObject& ball2 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, lambertProgram));
		DrawableObject& ball3 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, phongProgram));
		DrawableObject& ball4 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, blinnProgram));

		ambientProgram.setUniform("objectColor", 0.385f, 0.647f, 0.812f);
		lambertProgram.setUniform("objectColor", 0.385f, 0.647f, 0.812f);
		phongProgram.setUniform("objectColor", 0.385f, 0.647f, 0.812f);
		blinnProgram.setUniform("objectColor", 0.385f, 0.647f, 0.812f);

		lambertProgram.setUniform("lightPosition", 0.0f, 0.0f, 0.0f);
		phongProgram.setUniform("lightPosition", 0.0f, 0.0f, 0.0f);
		blinnProgram.setUniform("lightPosition", 0.0f, 0.0f, 0.0f);

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

