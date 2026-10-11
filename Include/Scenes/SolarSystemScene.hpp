#pragma once

#include "Scene.h"
#include "../Objects/DrawableObjectFactory.h"
#include "SceneSignature.hpp"
#include <utility>

class SolarSystemScene : public Scene
{
public:
    SolarSystemScene() : Scene("Solar system")
    {
        ShaderProgram& planetProgram = addShaderProgram("shaders/right.vert", "shaders/right.frag");

        const float earthOrbitRadius = 0.56f;
        const float earthOrbitSpeed = 20.0f;
        const float earthOrbitAngle = 25.0f;
        const float moonOrbitRadius = 0.17f;
        const float moonOrbitSpeed = 65.0f;
        const float orbitTilt = 30.0f;

        DrawableObject& solarSun = addObject(DrawableObjectFactory::create(ObjectType::Sun, planetProgram));
        solarSun.transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, 12.0f);
        solarSun.transformation.scale(0.19f);

        Transformation earthOrbit;
        earthOrbit.rotate(earthOrbitAngle, 0.0f, 0.0f, 1.0f, earthOrbitSpeed);
        earthOrbit.translate(earthOrbitRadius, 0.0f, 0.0f);

        DrawableObject& earthObject = addObject(DrawableObjectFactory::create(ObjectType::Earth, planetProgram));
        earthObject.transformation.rotate(orbitTilt, 1.0f, 0.0f, 0.0f);
        earthObject.transformation.add(std::move(earthOrbit));

        earthObject.transformation.rotate(23.5f, 0.0f, 0.0f, 1.0f);
        earthObject.transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, 80.0f);
        earthObject.transformation.scale(0.10f);

        Transformation moonEarthOrbit;
        moonEarthOrbit.rotate(earthOrbitAngle, 0.0f, 0.0f, 1.0f, earthOrbitSpeed);
        moonEarthOrbit.translate(earthOrbitRadius, 0.0f, 0.0f);

        Transformation moonOrbit;
        moonOrbit.rotate(110.0f, 0.0f, 0.0f, 1.0f, moonOrbitSpeed);
        moonOrbit.translate(moonOrbitRadius, 0.0f, 0.0f);
        moonEarthOrbit.add(std::move(moonOrbit));

        DrawableObject& moonObject = addObject(DrawableObjectFactory::create(ObjectType::Moon, planetProgram));
        moonObject.transformation.rotate(orbitTilt, 1.0f, 0.0f, 0.0f);
        moonObject.transformation.add(std::move(moonEarthOrbit));
        moonObject.transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, 15.0f);
        moonObject.transformation.scale(0.045f);
        addSignature(*this);
    }
};
