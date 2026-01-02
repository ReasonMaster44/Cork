#include "engine/input_manager.h"
#include "engine/window.h"

#include <GLFW/glfw3.h>

Cork::InputManager::InputManager(Window* window) 
    : window(window) {

    keyHist[0] = -1;
    keyHist[1] = -1;
}

void Cork::InputManager::updateCursor() {
    glfwGetCursorPos(window->win, &mx, &my);

    relMx = mx - lastMx;
    relMy = my - lastMy;
}

void Cork::InputManager::update() {
    keyHist[0] = keyHist[1];

    if (keyLeft()) {
        keyHist[1] = GLFW_KEY_LEFT;
    } else if (keyRight()) {
        keyHist[1] = GLFW_KEY_RIGHT;
    } else {
        keyHist[1] = -1;
    }
}

void Cork::InputManager::updateLastMousePos() {
    lastMx = mx;
    lastMy = my;
}

bool Cork::InputManager::keyA() { return glfwGetKey(window->win, GLFW_KEY_A); }
bool Cork::InputManager::keyB() { return glfwGetKey(window->win, GLFW_KEY_B); }
bool Cork::InputManager::keyC() { return glfwGetKey(window->win, GLFW_KEY_C); }
bool Cork::InputManager::keyD() { return glfwGetKey(window->win, GLFW_KEY_D); }
bool Cork::InputManager::keyE() { return glfwGetKey(window->win, GLFW_KEY_E); }
bool Cork::InputManager::keyF() { return glfwGetKey(window->win, GLFW_KEY_F); }
bool Cork::InputManager::keyG() { return glfwGetKey(window->win, GLFW_KEY_G); }
bool Cork::InputManager::keyH() { return glfwGetKey(window->win, GLFW_KEY_H); }
bool Cork::InputManager::keyI() { return glfwGetKey(window->win, GLFW_KEY_I); }
bool Cork::InputManager::keyJ() { return glfwGetKey(window->win, GLFW_KEY_J); }
bool Cork::InputManager::keyK() { return glfwGetKey(window->win, GLFW_KEY_K); }
bool Cork::InputManager::keyL() { return glfwGetKey(window->win, GLFW_KEY_L); }
bool Cork::InputManager::keyM() { return glfwGetKey(window->win, GLFW_KEY_M); }
bool Cork::InputManager::keyN() { return glfwGetKey(window->win, GLFW_KEY_N); }
bool Cork::InputManager::keyO() { return glfwGetKey(window->win, GLFW_KEY_O); }
bool Cork::InputManager::keyP() { return glfwGetKey(window->win, GLFW_KEY_P); }
bool Cork::InputManager::keyQ() { return glfwGetKey(window->win, GLFW_KEY_Q); }
bool Cork::InputManager::keyR() { return glfwGetKey(window->win, GLFW_KEY_R); }
bool Cork::InputManager::keyS() { return glfwGetKey(window->win, GLFW_KEY_S); }
bool Cork::InputManager::keyT() { return glfwGetKey(window->win, GLFW_KEY_T); }
bool Cork::InputManager::keyU() { return glfwGetKey(window->win, GLFW_KEY_U); }
bool Cork::InputManager::keyV() { return glfwGetKey(window->win, GLFW_KEY_V); }
bool Cork::InputManager::keyW() { return glfwGetKey(window->win, GLFW_KEY_W); }
bool Cork::InputManager::keyX() { return glfwGetKey(window->win, GLFW_KEY_X); }
bool Cork::InputManager::keyY() { return glfwGetKey(window->win, GLFW_KEY_Y); }
bool Cork::InputManager::keyZ() { return glfwGetKey(window->win, GLFW_KEY_Z); }

bool Cork::InputManager::key1() { return glfwGetKey(window->win, GLFW_KEY_1); }
bool Cork::InputManager::key2() { return glfwGetKey(window->win, GLFW_KEY_2); }
bool Cork::InputManager::key3() { return glfwGetKey(window->win, GLFW_KEY_3); }
bool Cork::InputManager::key4() { return glfwGetKey(window->win, GLFW_KEY_4); }
bool Cork::InputManager::key5() { return glfwGetKey(window->win, GLFW_KEY_5); }
bool Cork::InputManager::key6() { return glfwGetKey(window->win, GLFW_KEY_6); }
bool Cork::InputManager::key7() { return glfwGetKey(window->win, GLFW_KEY_7); }
bool Cork::InputManager::key8() { return glfwGetKey(window->win, GLFW_KEY_8); }
bool Cork::InputManager::key9() { return glfwGetKey(window->win, GLFW_KEY_9); }
bool Cork::InputManager::key0() { return glfwGetKey(window->win, GLFW_KEY_0); }

bool Cork::InputManager::keyLeft()  { return glfwGetKey(window->win, GLFW_KEY_LEFT);  }
bool Cork::InputManager::keyRight() { return glfwGetKey(window->win, GLFW_KEY_RIGHT); }
bool Cork::InputManager::keyUp()    { return glfwGetKey(window->win, GLFW_KEY_UP);    }
bool Cork::InputManager::keyDown()  { return glfwGetKey(window->win, GLFW_KEY_DOWN);  }

bool Cork::InputManager::clickKeyLeft() { return keyHist[1] == GLFW_KEY_LEFT && keyHist[0] != GLFW_KEY_LEFT; }

bool Cork::InputManager::clickKeyRight() { return keyHist[1] == GLFW_KEY_RIGHT && keyHist[0] != GLFW_KEY_RIGHT; }

bool Cork::InputManager::keySpace() { return glfwGetKey(window->win, GLFW_KEY_SPACE); }
