#pragma once

#include <glm/glm.hpp>

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

namespace Cork {

struct Entity {
    VBO vbo;
    IBO ibo;
    VAO vao;

    glm::vec3 pos;
    glm::vec3 scale;
    glm::vec3 colour;

    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 orientation = glm::mat4(1.0f);


    Entity(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour);

    void move(glm::vec3 offset);

    void setPos(glm::vec3 newPos);

    void rotateAround(float angle, glm::vec3 axis, glm::vec3 point);
    
    void rotate(glm::vec3 _rotation);

    void updateModel();
};

}