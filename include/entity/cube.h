#pragma once

#include "entity/mesh.h"
#include "glm/glm.hpp"

namespace Cork {

struct Cube : Cork::Mesh {
    Cube();
    
    Cube(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour = glm::vec3(0.0f));

    void colourFace(glm::vec3 face, glm::vec3 colour);

    void colourTopFace(glm::vec3 colour);
    void colourBottomFace(glm::vec3 colour);
    void colourFrontFace(glm::vec3 colour);
    void colourBackFace(glm::vec3 colour);
    void colourLeftFace(glm::vec3 colour);
    void colourRightFace(glm::vec3 colour);

    bool collide(Cork::Cube* cube);

};

}