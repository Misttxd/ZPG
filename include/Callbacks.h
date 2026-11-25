#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


void error_callback(int error, const char* description);

void registerCallbacks(GLFWwindow* window, void* pointer);
