#pragma once

#include "glm/glm.hpp"
#include "entity/entity.h"

namespace Cork {

struct LightSource : Cork::Entity {
    glm::vec3 facing;
    glm::vec3 colour;

    glm::mat4 view;
    glm::mat4 projection;

    glm::mat4 orthogonalProjection;
    glm::mat4 perspectiveProjection;

    LightSource();

    LightSource(glm::vec3 pos, glm::vec3 facing, glm::vec3 colour = glm::vec3(1.0f));

    void move(glm::vec3 offset);

    void update() override;
};
}