#pragma once

#include "Scene.h"
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

class SceneManager
{
public:
    void addScene(std::unique_ptr<Scene> scene)
    {
        if (!scene)
            throw std::invalid_argument("Scene must not be null.");

        scenes.push_back(std::move(scene));
    }

    void switchScene(std::size_t index)
    {
        if (index < scenes.size())
            activeScene = index;
    }

    Scene& getActiveScene()
    {
        return *scenes.at(activeScene);
    }

    bool handleKey(int key, int action)
    {
        if (action != GLFW_PRESS || scenes.empty())
            return false;

        if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
            switchScene(static_cast<std::size_t>(key - GLFW_KEY_1));
        else if (key == GLFW_KEY_TAB)
            switchScene((activeScene + 1) % scenes.size());
        else
            return false;

        return true;
    }

    void clear()
    {
        scenes.clear();
        activeScene = 0;
    }

private:
    std::vector<std::unique_ptr<Scene>> scenes;
    std::size_t activeScene = 0;
};
