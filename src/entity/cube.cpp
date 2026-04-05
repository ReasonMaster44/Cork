#include <algorithm>
#include <iostream>
#include <glm/glm.hpp>

#include "entity/cube.h"
#include "entity/mesh.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

Cork::Cube::Cube() {}

Cork::Cube::Cube(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour) 
    : Mesh(pos, scale, colour) {

    std::vector<glm::vec3> frontPositions {glm::vec3(-1.0f,  1.0f,  1.0f),
                                        glm::vec3( 1.0f,  1.0f,  1.0f),
                                        glm::vec3(-1.0f, -1.0f,  1.0f),
                                        glm::vec3( 1.0f, -1.0f,  1.0f)};

    std::vector<glm::vec3> backPositions {glm::vec3(-1.0f,  1.0f, -1.0f),
                                        glm::vec3( 1.0f,  1.0f, -1.0f),
                                        glm::vec3(-1.0f, -1.0f, -1.0f),
                                        glm::vec3( 1.0f, -1.0f, -1.0f)};

    std::vector<glm::vec3> leftPositions {glm::vec3(-1.0f,  1.0f, -1.0f),
                                        glm::vec3(-1.0f,  1.0f,  1.0f),
                                        glm::vec3(-1.0f, -1.0f, -1.0f),
                                        glm::vec3(-1.0f, -1.0f,  1.0f)};

    std::vector<glm::vec3> rightPositions {glm::vec3(1.0f,  1.0f, -1.0f),
                                        glm::vec3(1.0f,  1.0f,  1.0f),
                                        glm::vec3(1.0f, -1.0f, -1.0f),
                                        glm::vec3(1.0f, -1.0f,  1.0f)};

    std::vector<glm::vec3> topPositions {glm::vec3(-1.0f,  1.0f, -1.0f),
                                        glm::vec3( 1.0f,  1.0f, -1.0f),
                                        glm::vec3(-1.0f,  1.0f,  1.0f),
                                        glm::vec3( 1.0f,  1.0f,  1.0f)};

    std::vector<glm::vec3> bottomPositions {glm::vec3(-1.0f, -1.0f, -1.0f),
                                            glm::vec3( 1.0f, -1.0f, -1.0f),
                                            glm::vec3(-1.0f, -1.0f,  1.0f),
                                            glm::vec3( 1.0f, -1.0f,  1.0f)};

    std::vector<unsigned int> indices {0, 1, 2, 1, 2, 3};

    addFace(frontPositions, indices, colour);
    addFace(backPositions, indices, colour);
    addFace(leftPositions, indices, colour);
    addFace(rightPositions, indices, colour);
    addFace(topPositions, indices, colour);
    addFace(bottomPositions, indices, colour);

    updateBuffers();
}
/*
void Cork::Cube::updateBuffers() {
    vbo = VBO(cvd, sizeof(cvd));
    ibo = IBO(cubeIndexData, sizeof(cubeIndexData));
    vbo.bind();
    vao = VAO(layout, numberOfVertAttributes);
}
*/

void Cork::Cube::colourFace(glm::vec3 face, glm::vec3 colour) {
    int faceIndex;

    if (face == glm::vec3( 0.0f,  0.0f,  1.0f)) { faceIndex = 0; }
    if (face == glm::vec3( 0.0f,  0.0f, -1.0f)) { faceIndex = 1; }
    if (face == glm::vec3(-1.0f,  0.0f,  0.0f)) { faceIndex = 2; }
    if (face == glm::vec3( 1.0f,  0.0f,  0.0f)) { faceIndex = 3; }
    if (face == glm::vec3( 0.0f,  1.0f,  0.0f)) { faceIndex = 4; }
    if (face == glm::vec3( 0.0f, -1.0f,  0.0f)) { faceIndex = 5; }

    for (int i = faceIndex * 4; i < (faceIndex + 1) * 4; i++) {
        vertexColours[i] = colour;
    }

    updateBuffers();
}

void Cork::Cube::colourFrontFace(glm::vec3 colour)  { colourFace(glm::vec3( 0.0f,  0.0f,  1.0f), colour); }
void Cork::Cube::colourBackFace(glm::vec3 colour)   { colourFace(glm::vec3( 0.0f,  0.0f, -1.0f), colour); }
void Cork::Cube::colourLeftFace(glm::vec3 colour)   { colourFace(glm::vec3(-1.0f,  0.0f,  0.0f), colour); }
void Cork::Cube::colourRightFace(glm::vec3 colour)  { colourFace(glm::vec3( 1.0f,  0.0f,  0.0f), colour); }
void Cork::Cube::colourTopFace(glm::vec3 colour)    { colourFace(glm::vec3( 0.0f,  1.0f,  0.0f), colour); }
void Cork::Cube::colourBottomFace(glm::vec3 colour) { colourFace(glm::vec3( 0.0f, -1.0f,  0.0f), colour); }

bool Cork::Cube::collide(Cork::Cube* cube) {
    return (cube->pos.x - cube->scale.x >= pos.x - scale.x && cube->pos.x + cube->scale.x <= pos.x + scale.x &&
            cube->pos.y - cube->scale.y >= pos.y - scale.y && cube->pos.y + cube->scale.y <= pos.y + scale.y &&
            cube->pos.z - cube->scale.z >= pos.z - scale.z && cube->pos.z + cube->scale.z <= pos.z + scale.z);
}