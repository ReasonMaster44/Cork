#include "glm/glm.hpp"

#include "entity/mesh.h"
#include <string>

namespace Cork {

struct Vertex {
    glm::vec3 pos;
    glm::vec3 norm;

    Vertex(glm::vec3 pos, glm::vec3 norm);
};

struct Material {
    glm::vec3 diffuse;

    Material(glm::vec3 diffuse);
};

struct Model : Cork::Mesh {
    Model(std::string objFilePath, std::string mtlFilePath, glm::vec3 pos, glm::vec3 scale, glm::vec3 colour);
};

}