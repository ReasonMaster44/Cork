#pragma once

#include <glm/glm.hpp>

#include "entity/entity.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"
#include "opengl/shader.h"

namespace Cork {

struct Mesh : Cork::Entity {
    Cork::VBO vbo;
    Cork::IBO ibo;
    Cork::VAO vao;

    Cork::Shader* shader;

    glm::vec3 scale;
    glm::vec3 colour;
    glm::mat4 model = glm::mat4(1.0f);

    std::vector<glm::vec3> vertexPositions;
    std::vector<glm::vec3> vertexNormals;
    std::vector<glm::vec3> vertexColours;

    std::vector<unsigned int> indices;

    void updateBuffers();

    unsigned int layout[3] = {3, 3, 3};

    Mesh();
    Mesh(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour);

    void addTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 colour);
    void addFace(std::vector<glm::vec3> positions, std::vector<unsigned int> indices, glm::vec3 colour, glm::vec3 offset = glm::vec3(0.0f));

    void update() override;

    bool rayIntersect(glm::vec3 rayOrigin, glm::vec3 rayDir);

};

}