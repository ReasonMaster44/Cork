#include <iostream>

#include "entity/mesh.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Cork::Mesh::Mesh() {}

Cork::Mesh::Mesh(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour)
    : Cork::Entity(pos), scale(scale), colour(colour) {

    update();
}

void Cork::Mesh::update() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = model * orientation;
    model = glm::scale(model, scale);
}
