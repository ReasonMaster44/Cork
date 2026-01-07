#pragma once

#include "entity/entity.h"
#include "glm/glm.hpp"

namespace Cork {

struct Cube : Entity {
    static float cubeVertexData[216];
    static unsigned int cubeIndexData[36];

    static constexpr unsigned int floatsPerAttribute = 3;
    static constexpr unsigned int numberOfVertAttributes = 3;

    static unsigned int layout[numberOfVertAttributes];

    static constexpr unsigned int floatsPerFace = 4 * floatsPerAttribute * numberOfVertAttributes;

    float cvd[216];

    Cube(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour);

    void updateBuffers();

    void colourFace(glm::vec3 face, glm::vec3 colour);

    void colourTopFace(glm::vec3 colour);
    void colourBottomFace(glm::vec3 colour);
    void colourFrontFace(glm::vec3 colour);
    void colourBackFace(glm::vec3 colour);
    void colourLeftFace(glm::vec3 colour);
    void colourRightFace(glm::vec3 colour);

};

}