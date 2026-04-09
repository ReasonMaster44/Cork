#include "engine/window.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Cork::Window::Window(unsigned int win_w, unsigned int win_h, const char *title) 
    : WIN_W(win_w), WIN_H(win_h) {
    win = glfwCreateWindow(WIN_W, WIN_H, title, nullptr, nullptr);
    
    if (!win) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(win);
    //glfwSwapInterval(0); // Vsync
    //glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialise glad:
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { std::cerr << "Failed to initialise glad" << std::endl; }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    
    glfwGetFramebufferSize(win, &frameBufferWidth, &frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    lastTime = glfwGetTime();
    currentTime = glfwGetTime();
}

bool Cork::Window::shouldClose() {
    return glfwWindowShouldClose(win);
}

void Cork::Window::disableCursor() {
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Cork::Window::enableCursor() {
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Cork::Window::update() {
    frameCount++;

    currentTime = glfwGetTime();

    if (currentTime - lastTime >= 1.0) {
        fps = frameCount / (currentTime - lastTime);
        frameCount = 0;
        lastTime = currentTime;
    }
}