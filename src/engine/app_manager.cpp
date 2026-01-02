#include "engine/app_manager.h"
#include <iostream>
#include <GLFW/glfw3.h>

Cork::AppManager::AppManager() {
    if (!glfwInit()) { std::cerr << "Failed to initialise GLFW" << std::endl; }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For mac
}
