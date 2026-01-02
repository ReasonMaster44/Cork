#pragma once

#include "entity.h"

namespace Cork {

struct Plane : Entity {
    Plane(glm::vec3 pos, glm::vec2 scale, glm::vec3 colour);
};

}