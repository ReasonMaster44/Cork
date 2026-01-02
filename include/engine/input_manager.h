#include "engine/window.h"

namespace Cork {

struct InputManager {
    float relMx, relMy;
    double mx, my;
    float lastMx, lastMy;
    
    Window* window;

    int keyHist[2];

    InputManager(Window* window);

    void updateCursor();

    void update();

    void updateLastMousePos();

    bool keyA();
    bool keyB();
    bool keyC();
    bool keyD();
    bool keyE();
    bool keyF();
    bool keyG();
    bool keyH();
    bool keyI();
    bool keyJ();
    bool keyK();
    bool keyL();
    bool keyM();
    bool keyN();
    bool keyO();
    bool keyP();
    bool keyQ();
    bool keyR();
    bool keyS();
    bool keyT();
    bool keyU();
    bool keyV();
    bool keyW();
    bool keyX();
    bool keyY();
    bool keyZ();

    bool key1();
    bool key2();
    bool key3();
    bool key4();
    bool key5();
    bool key6();
    bool key7();
    bool key8();
    bool key9();
    bool key0();

    bool keyLeft();
    bool keyRight();
    bool keyUp();
    bool keyDown();

    bool clickKeyLeft();

    bool clickKeyRight();

    bool keySpace();
};

}