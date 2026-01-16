#include <iostream>

#include "entity/entity.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Cork::Entity::Entity() {}

Cork::Entity::Entity(glm::vec3 pos)
    : pos(pos) {

    update();
}

void Cork::Entity::move(glm::vec3 offset) {
    pos += offset;
    update();
}

void Cork::Entity::setPos(glm::vec3 newPos) {
    pos = newPos;
    update();
}

void Cork::Entity::rotateAround(float angle, glm::vec3 axis, glm::vec3 point) {
    glm::mat4 m(1.0f);
    m = glm::translate(m, point);
    m = glm::rotate(m, angle, glm::normalize(axis));
    m = glm::translate(m, -point);

    pos = glm::vec3(m * glm::vec4(pos, 1.0f));

    orientation = glm::rotate(glm::mat4(1.0f), angle, glm::normalize(axis)) * orientation;
    
    update();
}

void Cork::Entity::rotate(glm::vec3 _rotation) {
    rotation += _rotation;
    update();
}

void Cork::Entity::update() {}