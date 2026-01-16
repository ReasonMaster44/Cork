#include "camera.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

#include "entity/entity.h"

#include <glm/gtc/matrix_transform.hpp>

Cork::Camera::Camera() {}

Cork::Camera::Camera(glm::vec3 pos, float yaw, float pitch) 
    : Cork::Entity(pos), yaw(yaw), pitch(pitch) {
        
    //view = glm::translate(view, pos);
    update();
}

void Cork::Camera::update() {
    glm::vec3 _lookAtTarget;

    if (setLookAt) {
        front = glm::normalize(lookAtTarget - pos);
    } else {
        glm::vec3 _front = glm::vec3( cos(glm::radians(yaw)) * cos(glm::radians(pitch)), 
                                    sin(glm::radians(pitch)),
                                    -sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

        _front.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        _front.y = sin(glm::radians(pitch));
        _front.z = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        
        front = glm::normalize(_front);

        _lookAtTarget = pos + front;
    }

    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);

    // Calculate right and up vectors
    glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
    glm::vec3 up    = glm::cross(right, front);

    view = glm::lookAt(pos, _lookAtTarget, up);
}

void Cork::Camera::lookAt(glm::vec3 point) {
    lookAtTarget = point;
    setLookAt = true;
}