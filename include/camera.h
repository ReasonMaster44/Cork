#pragma once

#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

namespace Cork {

struct Camera {
    glm::vec3 pos;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    
    glm::mat4 view = glm::mat4(1.0f);

    float yaw;
    float pitch;

    float maxSpeed = 0.15f;
    float speed = 0.0f;
    float yVelMax = 0.2f;
    float yVelDefault = 0.06f;
    float yVel = yVelDefault;

    float sens = 0.06;

    Camera();

    Camera(glm::vec3 pos = glm::vec3(0.0f), float yaw = 270.0f, float pitch = 0.0f);

    void updateViewMatrix();

    void rotate(float relMouseX, float relMouseY);

    void move(glm::vec3 move);
};

}