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

void Cork::Entity::rotate(glm::vec3 _rotation) {
    rotation += _rotation;
    updateModel();
}

void Cork::Entity::updateModel() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);

    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));    
}
