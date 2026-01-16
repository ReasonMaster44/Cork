#include <algorithm>
#include <iostream>

#include "entity/cube.h"
#include "entity/mesh.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

// Flat shading:
float Cork::Cube::cubeVertexData[216] = {
    // Positions            // Flat Normals         // Colours

    // Front face (+Z)
    -1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f,     0.8f, 0.2f, 0.3f, // Top left
     1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f,     0.8f, 0.2f, 0.3f, // Top right
    -1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f,     0.8f, 0.2f, 0.3f, // Bottom left
     1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f,     0.8f, 0.2f, 0.3f, // Bottom right

    // Back face (-Z)
    -1.0f,  1.0f, -1.0f,     0.0f,  0.0f, -1.0f,     0.8f, 0.2f, 0.3f, // Top left
     1.0f,  1.0f, -1.0f,     0.0f,  0.0f, -1.0f,     0.8f, 0.2f, 0.3f, // Top right
    -1.0f, -1.0f, -1.0f,     0.0f,  0.0f, -1.0f,     0.8f, 0.2f, 0.3f, // Bottom left
     1.0f, -1.0f, -1.0f,     0.0f,  0.0f, -1.0f,     0.8f, 0.2f, 0.3f, // Bottom right

    // Left face (-X)
    -1.0f,  1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,     0.8f, 0.2f, 0.3f, // Top left
    -1.0f,  1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,     0.8f, 0.2f, 0.3f, // Top right
    -1.0f, -1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,     0.8f, 0.2f, 0.3f, // Bottom left
    -1.0f, -1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Bottom right

    // Right face (+X)
     1.0f,  1.0f, -1.0f,     1.0f,  0.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Top left
     1.0f,  1.0f,  1.0f,     1.0f,  0.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Top right
     1.0f, -1.0f, -1.0f,     1.0f,  0.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Bottom left
     1.0f, -1.0f,  1.0f,     1.0f,  0.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Bottom right

    // Top face (+Y)
    -1.0f,  1.0f, -1.0f,     0.0f,  1.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Top left
     1.0f,  1.0f, -1.0f,     0.0f,  1.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Top right
    -1.0f,  1.0f,  1.0f,     0.0f,  1.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Bottom left
     1.0f,  1.0f,  1.0f,     0.0f,  1.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Bottom right

    // Bottom face (-Y)
    -1.0f, -1.0f, -1.0f,     0.0f, -1.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Top left
     1.0f, -1.0f, -1.0f,     0.0f, -1.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Top right
    -1.0f, -1.0f,  1.0f,     0.0f, -1.0f,  0.0f,     0.4f, 0.7f, 0.6f, // Bottom left
     1.0f, -1.0f,  1.0f,     0.0f, -1.0f,  0.0f,     0.4f, 0.7f, 0.6f  // Bottom right
};

unsigned int Cork::Cube::cubeIndexData[] = {
    // Front face (+Z)
    0, 1, 2,
    1, 3, 2,

    // Back face (-Z)
    4, 5, 6,
    5, 7, 6,

    // Left face (-X)
    8, 9, 10,
    9, 11, 10,

    // Right face (+X)
    12, 13, 14,
    13, 15, 14,

    // Top face (+Y)
    16, 17, 18,
    17, 19, 18,

    // Bottom face (-Y)
    20, 21, 22,
    21, 23, 22
};

unsigned int Cork::Cube::layout[3] = {Cork::Cube::floatsPerAttribute, Cork::Cube::floatsPerAttribute, Cork::Cube::floatsPerAttribute};

Cork::Cube::Cube() {}

Cork::Cube::Cube(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour) 
    : Mesh(pos, scale, colour) {


    std::copy(std::begin(cubeVertexData), std::end(cubeVertexData), std::begin(cvd));
    
    int offset = 0;
    for (int i = 0; i < 216; i++) {
        if (i % (floatsPerAttribute * numberOfVertAttributes) == 0) {
            offset = 0;
        }

        if (offset == 6) {cvd[i] = colour.x;}
        if (offset == 7) {cvd[i] = colour.y;}
        if (offset == 8) {cvd[i] = colour.z;}

        offset += 1;
    }

    updateBuffers();
}

void Cork::Cube::updateBuffers() {
    vbo = VBO(cvd, sizeof(cvd));
    ibo = IBO(cubeIndexData, sizeof(cubeIndexData));
    vbo.bind();
    vao = VAO(layout, numberOfVertAttributes);
}
void Cork::Cube::colourFace(glm::vec3 face, glm::vec3 colour) {
    int faceIndex;

    if (face == glm::vec3( 0.0f,  0.0f,  1.0f)) { faceIndex = 0; }
    if (face == glm::vec3( 0.0f,  0.0f, -1.0f)) { faceIndex = 1; }
    if (face == glm::vec3(-1.0f,  0.0f,  0.0f)) { faceIndex = 2; }
    if (face == glm::vec3( 1.0f,  0.0f,  0.0f)) { faceIndex = 3; }
    if (face == glm::vec3( 0.0f,  1.0f,  0.0f)) { faceIndex = 4; }
    if (face == glm::vec3( 0.0f, -1.0f,  0.0f)) { faceIndex = 5; }


    int offset = 0;
    for (int i = faceIndex * floatsPerFace; i < faceIndex * floatsPerFace + floatsPerFace; i++) {
        if (i % (floatsPerAttribute * numberOfVertAttributes) == 0) {
            offset = 0;
        }

        if (offset == 6) {cvd[i] = colour.x;}
        if (offset == 7) {cvd[i] = colour.y;}
        if (offset == 8) {cvd[i] = colour.z;}

        offset += 1;
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