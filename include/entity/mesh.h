#pragma once

#include <glm/glm.hpp>

#include "entity/entity.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

namespace Cork {

struct Mesh : Cork::Entity {
    VBO vbo;
    IBO ibo;
    VAO vao;

    glm::vec3 scale;
    glm::vec3 colour;
    glm::mat4 model = glm::mat4(1.0f);

    Mesh();
    Mesh(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour);

    void update() override;
};

}