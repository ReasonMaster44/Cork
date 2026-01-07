#include "camera.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

#include <glm/gtc/matrix_transform.hpp>

Cork::Camera::Camera() {}

Cork::Camera::Camera(glm::vec3 pos, float yaw, float pitch) 
    : pos(pos), yaw(yaw), pitch(pitch) {
        
    //view = glm::translate(view, pos);
    updateViewMatrix();
}

void Cork::Camera::updateViewMatrix() {
    glm::vec3 _front = glm::vec3( cos(glm::radians(yaw)) * cos(glm::radians(pitch)), 
                                  sin(glm::radians(pitch)),
                                 -sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

    _front.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    _front.y = sin(glm::radians(pitch));
    _front.z = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    front = glm::normalize(_front);

    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);

    // Calculate right and up vectors
    glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
    glm::vec3 up    = glm::cross(right, front);

    // View matrix
    view = glm::lookAt(pos, pos + front, up);
}

void Cork::Camera::rotate(float relMouseX, float relMouseY) {
    yaw += relMouseX * sens;
    pitch += relMouseY * sens;
}

void Cork::Camera::move(glm::vec3 move) {
    //pos.x += cos(glm::radians(yaw)) * speed;
    //pos.z += sin(glm::radians(yaw)) * speed;
    pos += move;
    updateViewMatrix();
}