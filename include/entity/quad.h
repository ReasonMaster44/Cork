#pragma once

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"
#include "opengl/texture.h"
#include "opengl/shader.h"

#include "glm/glm.hpp"

namespace Cork {

struct Quad {
    VBO vbo;
    IBO ibo;
    VAO vao;

    glm::vec2 pos;
    glm::vec2 scale;
    glm::vec3 colour;

    float rotation = 0.0f;

    glm::mat4 model;

    Texture* texture = nullptr;

    Quad();
    
    Quad(glm::vec2 pos, glm::vec2 scale, glm::vec3 colour);

    void addTexture(Texture* _texture);

    void move(glm::vec2 offset);

    void setPos(glm::vec2 newPos);

    void rotate(float _rotation);

    void updateModel();
};

}