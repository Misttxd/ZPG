#pragma once

#include "Scene.h"
#include "SceneSignature.hpp"
#include "DrawableObjectFactory.h"
#include <cstdlib>


class LightingScene : public Scene
{
public:
	LightingScene(bool normalTest = false) : Scene(normalTest ? "Normal test" : "Lighting")
	{
		createCamera();
		ShaderProgram& ambientProgram = addShaderProgram("shaders/lighting.vert", "shaders/ambient.frag");
		ShaderProgram& lambertProgram = addShaderProgram("shaders/lighting.vert", "shaders/lambert.frag");
		ShaderProgram& phongProgram = addShaderProgram("shaders/lighting.vert", "shaders/phong.frag");
		ShaderProgram& blinnProgram = addShaderProgram("shaders/lighting.vert", "shaders/blinnPhong.frag");

		DrawableObject& ball1 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, normalTest ? phongProgram : ambientProgram));
		DrawableObject& ball2 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, normalTest ? phongProgram : lambertProgram));
		DrawableObject& ball3 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, normalTest ? phongProgram : phongProgram));
		DrawableObject& ball4 = addObject(DrawableObjectFactory::create(ObjectType::Sphere, normalTest ? phongProgram : blinnProgram));
	
		phongProgram.setUniform("attenuationFactors", 1.0f, 0.0f, 0.0f);

		ambientProgram.setUniform("objectColor", 0.385f, 0.647f, 0.812f);
		lambertProgram.setUniform("objectColor", 0.385f, 0.647f, 0.812f);
		phongProgram.setUniform("objectColor", 0.385f, 0.647f, 0.812f);
		blinnProgram.setUniform("objectColor", 0.385f, 0.647f, 0.812f);

		lambertProgram.setUniform("lightPosition", 0.0f, 0.0f, 0.0f);
		phongProgram.setUniform("lightPosition", 0.0f, 0.0f, 0.0f);
		blinnProgram.setUniform("lightPosition", 0.0f, 0.0f, 0.0f);

		if (normalTest)
		{
			// Strong attenuation test: near sphere on the left, far sphere on the right.
			phongProgram.setUniform("attenuationFactors", 1.0f, 0.0f, 0.5f);
			phongProgram.setUniform("lightPosition", 0.0f, 0.0f, 0.0f);
		}

		ball1.transformation.translate(-0.9f, 0.0f, 0.0f);
		ball1.transformation.scale(0.4);

		ball2.transformation.translate(0.9f, 0.0f, normalTest ? -3.0f : 0.0f);
		ball2.transformation.scale(0.4);

		ball3.transformation.translate(0, 0.9, 0);

		if (normalTest)
		{
			ball3.transformation.rotate(35.0f, 0.0f, 0.0f, 1.0f);
			ball3.transformation.scale(0.6f, 0.25f, 0.4f);
		}
		else
		{
			ball3.transformation.scale(0.4f);
		}

		ball4.transformation.translate(0, -0.9, 0);
		ball4.transformation.scale(0.4);

	}

private:

};

