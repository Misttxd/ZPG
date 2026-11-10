#include "InputManager.h"
#include "camera.h"

void InputManager::handleKey(int key, int action)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (sceneManager.handleKey(key, action))
    {
        glfwSetWindowTitle(window, sceneManager.getActiveScene().getName().c_str());

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        handleResize(width, height);
        mouseDragging = false;
    }
    else if (action == GLFW_PRESS)
    {
        sceneManager.getActiveScene().onKeyPressed(key);
    }
}

void InputManager::handleResize(int width, int height)
{
    glViewport(0, 0, width, height);

    Camera* camera = sceneManager.getActiveScene().getCamera();
    if (camera)
    {
        camera->setPerspective(width, height);
    }
}

void InputManager::handleScroll(double yoffset)
{
    Camera* camera = sceneManager.getActiveScene().getCamera();

    if (!camera)
    {
        return;
    }

    camera->setSpeed(camera->getSpeed() + static_cast<float>(yoffset));
}

void InputManager::handleMouseButton(int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &clickX, &clickY);
        clickPending = true;
        return;
    }

    if (button != GLFW_MOUSE_BUTTON_RIGHT)
    {
        return;
    }

    mouseDragging = action == GLFW_PRESS;

    if (mouseDragging)
    {
        glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
    }
}

void InputManager::handleMouseMove(double x, double y)
{
    if (!mouseDragging || !glfwGetWindowAttrib(window, GLFW_FOCUSED))
    {
        return;
    }

    double deltaX = x - lastMouseX;
    double deltaY = y - lastMouseY;

    lastMouseX = x;
    lastMouseY = y;

    Camera* camera = sceneManager.getActiveScene().getCamera();

    if (camera)
    {
        camera->rotate(static_cast<float>(deltaX), static_cast<float>(deltaY));
    }
}

void InputManager::updateMovement(Scene& scene, double deltaTime)
{
    Camera* camera = scene.getCamera();

    if (camera && glfwGetWindowAttrib(window, GLFW_FOCUSED))
    {
        float forward = 0.0f;
        float sideways = 0.0f;
        float vertical = 0.0f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) forward += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) forward -= 1.0f;

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) sideways += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) sideways -= 1.0f;

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) vertical -= 1.0f;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) vertical += 1.0f;

        camera->move(forward, sideways, vertical, deltaTime);
    }
}

void InputManager::processClick(Scene& scene)
{
    if (clickPending)
    {
        clickPending = false;

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        GLint x = static_cast<GLint>(clickX);
        GLint y = static_cast<GLint>(clickY);
        scene.readClickedPixel(x, y, width, height);
    }
}
