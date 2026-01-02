#include "entity/cube.h"
#include "entity/entity.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

// Flat shading:
float cubeVertexData[] = {
    // Positions            // Correct Flat Normals

    // Front face (+Z)
    -1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f, // Top left
     1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f, // Top right
    -1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f, // Bottom left
     1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f, // Bottom right

    // Back face (-Z)
    -1.0f,  1.0f, -1.0f,     0.0f,  0.0f, -1.0f, // Top left
     1.0f,  1.0f, -1.0f,     0.0f,  0.0f, -1.0f, // Top right
    -1.0f, -1.0f, -1.0f,     0.0f,  0.0f, -1.0f, // Bottom left
     1.0f, -1.0f, -1.0f,     0.0f,  0.0f, -1.0f, // Bottom right

    // Left face (-X)
    -1.0f,  1.0f, -1.0f,    -1.0f,  0.0f,  0.0f, // Top left
    -1.0f,  1.0f,  1.0f,    -1.0f,  0.0f,  0.0f, // Top right
    -1.0f, -1.0f, -1.0f,    -1.0f,  0.0f,  0.0f, // Bottom left
    -1.0f, -1.0f,  1.0f,    -1.0f,  0.0f,  0.0f, // Bottom right

    // Right face (+X)
     1.0f,  1.0f, -1.0f,     1.0f,  0.0f,  0.0f, // Top left
     1.0f,  1.0f,  1.0f,     1.0f,  0.0f,  0.0f, // Top right
     1.0f, -1.0f, -1.0f,     1.0f,  0.0f,  0.0f, // Bottom left
     1.0f, -1.0f,  1.0f,     1.0f,  0.0f,  0.0f, // Bottom right

    // Top face (+Y)
    -1.0f,  1.0f, -1.0f,     0.0f,  1.0f,  0.0f, // Top left
     1.0f,  1.0f, -1.0f,     0.0f,  1.0f,  0.0f, // Top right
    -1.0f,  1.0f,  1.0f,     0.0f,  1.0f,  0.0f, // Bottom left
     1.0f,  1.0f,  1.0f,     0.0f,  1.0f,  0.0f, // Bottom right

    // Bottom face (-Y)
    -1.0f, -1.0f, -1.0f,     0.0f, -1.0f,  0.0f, // Top left
     1.0f, -1.0f, -1.0f,     0.0f, -1.0f,  0.0f, // Top right
    -1.0f, -1.0f,  1.0f,     0.0f, -1.0f,  0.0f, // Bottom left
     1.0f, -1.0f,  1.0f,     0.0f, -1.0f,  0.0f  // Bottom right
};

unsigned int cubeIndexData[] = {
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

Cork::Cube::Cube(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour) 
    : Entity(pos, scale, colour) {
        
    unsigned int layout[] = {3, 3};

    vbo = VBO(cubeVertexData, sizeof(cubeVertexData));
    ibo = IBO(cubeIndexData, sizeof(cubeIndexData));

    vbo.bind();
    vao = VAO(layout, 2);
}