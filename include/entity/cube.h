#pragma once

#include "entity/entity.h"
#include "glm/glm.hpp"

namespace Cork {

struct Cube : Entity {
    Cube(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour);
};

}