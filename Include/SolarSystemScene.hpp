#pragma once

#include "Scene.h"
#include "DrawableObjectFactory.h"
#include "SceneSignature.hpp"
#include <utility>

class SolarSystemScene : public Scene
{
public:
    SolarSystemScene() : Scene("Solar system")
    {

        createCamera();
        

        ShaderProgram& sunProgram = addShaderProgram("shaders/vertexColorLighting.vert", "shaders/vertexColorAmbient.frag");

        ShaderProgram& planetProgram = addShaderProgram("shaders/vertexColorLighting.vert", "shaders/vertexColorPhong.frag");



        planetProgram.setUniform("lightPosition", 0.0, 0.0, 0.0);

        const float earthOrbitRadius = 0.62f;
        const float animationSpeed = 0.7f;
        const float earthOrbitSpeed = 20.0f * animationSpeed;
        const float earthOrbitAngle = 25.0f;
        const float earthRotationSpeed = earthOrbitSpeed * 365.256f / 0.99727f/10;
        const float moonOrbitRadius = 0.14f;
        const float moonOrbitSpeed = earthOrbitSpeed * 365.256f / 27.3217f;
        const float moonOrbitTilt = 5.145f;
        const float earthRadius = 0.065f;

        DrawableObject& solarSun = addObject(DrawableObjectFactory::create(ObjectType::Sun, sunProgram));
        solarSun.transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, earthOrbitSpeed * 365.256f / 25.38f);
        solarSun.transformation.scale(0.30f);

        Transformation earthOrbit;
        earthOrbit.rotate(earthOrbitAngle, 0.0f, 1.0f, 0.0f, earthOrbitSpeed);
        earthOrbit.translate(earthOrbitRadius, 0.0f, 0.0f);
        earthOrbit.rotate(-earthOrbitAngle, 0.0f, 1.0f, 0.0f, -earthOrbitSpeed);

        DrawableObject& earthObject = addObject(DrawableObjectFactory::create(ObjectType::Earth, planetProgram));
        earthObject.transformation.add(std::move(earthOrbit));

        earthObject.transformation.rotate(23.5f, 0.0f, 0.0f, 1.0f);
        earthObject.transformation.rotate(0.0f, 0.0f, 1.0f, 0.0f, earthRotationSpeed);
        earthObject.transformation.scale(earthRadius);

        Transformation moonEarthOrbit;
        moonEarthOrbit.rotate(earthOrbitAngle, 0.0f, 1.0f, 0.0f, earthOrbitSpeed);
        moonEarthOrbit.translate(earthOrbitRadius, 0.0f, 0.0f);
        moonEarthOrbit.rotate(-earthOrbitAngle, 0.0f, 1.0f, 0.0f, -earthOrbitSpeed);

        Transformation moonOrbit;
        moonOrbit.rotate(moonOrbitTilt, 1.0f, 0.0f, 0.0f);
        moonOrbit.rotate(110.0f, 0.0f, 1.0f, 0.0f, moonOrbitSpeed);
        moonOrbit.translate(moonOrbitRadius, 0.0f, 0.0f);
        moonEarthOrbit.add(std::move(moonOrbit));

        DrawableObject& moonObject = addObject(DrawableObjectFactory::create(ObjectType::Moon, planetProgram));

        moonObject.transformation.add(std::move(moonEarthOrbit));
        // The orbit rotation also turns the Moon: the same side faces Earth.
        moonObject.transformation.scale(earthRadius * (1737.5f / 6371.0f));

        DrawableObject& rocketObject = addObject(DrawableObjectFactory::create(ObjectType::Rocket, planetProgram));
        // An outer, tilted orbit keeps the rocket clear of the Earth and Moon.
        rocketObject.transformation.rotate(20.0f, 0.0f, 0.0f, 1.0f);
        rocketObject.transformation.rotate(135.0f, 0.0f, 1.0f, 0.0f, earthOrbitSpeed * 0.65f);
        rocketObject.transformation.translate(1.02f, 0.0f, 0.0f);
        // The exported rocket points along +Y; turn its nose along the flight path.
        rocketObject.transformation.rotate(-90.0f, 1.0f, 0.0f, 0.0f);
        rocketObject.transformation.scale(0.09f);

        addSignature(*this);
    }
};
