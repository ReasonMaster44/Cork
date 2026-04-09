#pragma once

#include <GLFW/glfw3.h>

namespace Cork {

struct Window {
    const unsigned int WIN_W;
    const unsigned int WIN_H;
    
    GLFWwindow* win;

    int frameBufferWidth, frameBufferHeight;

    int frameCount = 0;
    double lastTime;
    double currentTime;
    float fps;

    Window(unsigned int win_w, unsigned int win_h, const char *title);

    bool shouldClose();

    void disableCursor();
    void enableCursor();

    void update();
};

}