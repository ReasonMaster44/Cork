#pragma once

#include "entity/mesh.h"

namespace Cork {

struct Plane : Cork::Mesh {
    Plane(glm::vec3 pos, glm::vec2 scale, glm::vec3 colour);
};

}