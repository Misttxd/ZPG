#pragma once

#include "Scene/SceneManager.hpp"

class InputManager
{
public:
    InputManager(GLFWwindow*& window, SceneManager& sceneManager): window(window), sceneManager(sceneManager) {}

    void handleKey(int key, int action);
    void handleResize(int width, int height);
    void handleScroll(double yoffset);
    void handleMouseButton(int button, int action);
    void handleMouseMove(double x, double y);
    void updateMovement(Scene& scene, double deltaTime);
    void processClick(Scene& scene);

private:
    GLFWwindow*& window;
    SceneManager& sceneManager;
    bool mouseDragging = false;
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;

    bool clickPending = false;
    double clickX = 0.0;
    double clickY = 0.0;
};
