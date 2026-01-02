#include "glm/glm.hpp"

#include "entity.h"
#include <string>

namespace Cork {

struct Vertex {
    glm::vec3 pos;
    glm::vec3 norm;

    Vertex(glm::vec3 pos, glm::vec3 norm);
};

struct Model : Entity {
    Model(std::string objFilePath, glm::vec3 pos, glm::vec3 scale, glm::vec3 colour);
};

}