#include "light_source.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Cork::LightSource::LightSource() {}

Cork::LightSource::LightSource(glm::vec3 pos, glm::vec3 facing, glm::vec3 colour) 
    : Cork::Entity(pos), facing(facing), colour(colour) {
    
    orthogonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
    perspectiveProjection = glm::perspective(glm::radians(150.0f), 1.0f, 2.0f, 150.0f);

    projection = perspectiveProjection;

    update();
}

void Cork::LightSource::move(glm::vec3 offset) {
    pos += offset;
}

void Cork::LightSource::update() {
    glm::vec3 forward = glm::normalize(facing - pos);
    glm::vec3 worldUp = glm::vec3(0, 1, 0);

    if (glm::abs(glm::dot(forward, worldUp)) > 0.999f) { worldUp = glm::vec3(1, 0, 0); }

    view = glm::lookAt(pos, facing, worldUp);
}