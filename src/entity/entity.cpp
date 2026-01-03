#include "entity/entity.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Cork::Entity::Entity(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour)
    : pos(pos), scale(scale), colour(colour) {

    updateModel();
}

void Cork::Entity::move(glm::vec3 offset) {
    pos += offset;
    updateModel();
}

void Cork::Entity::setPos(glm::vec3 newPos) {
    pos = newPos;
    updateModel();
}

void Cork::Entity::rotateAround(float angle, glm::vec3 axis, glm::vec3 point) {
    glm::mat4 m(1.0f);
    m = glm::translate(m, point);
    m = glm::rotate(m, angle, glm::normalize(axis));
    m = glm::translate(m, -point);

    pos = glm::vec3(m * glm::vec4(pos, 1.0f));

    orientation = glm::rotate(glm::mat4(1.0f), angle, glm::normalize(axis)) * orientation;
    
    updateModel();
}

void Cork::Entity::rotate(glm::vec3 _rotation) {
    rotation += _rotation;
    updateModel();
}

void Cork::Entity::updateModel() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = model * orientation;
    model = glm::scale(model, scale);

    //model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    //model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    //model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));    
}
