#include "entity/plane.h"
#include "entity/entity.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

// Flat shading:
float planeVertexData[] = {
    // Positions            // Correct Flat Normals
    -1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f, // Top left
     1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f, // Top right
    -1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f, // Bottom left
     1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f  // Bottom right
};

unsigned int planeIndexData[] = {
    0, 1, 2,
    1, 3, 2
};

Cork::Plane::Plane(glm::vec3 pos, glm::vec2 scale, glm::vec3 colour) 
    : Entity(pos, glm::vec3(scale.x, scale.y, 0.0f), colour) {
        
    unsigned int layout[] = {3, 3};

    vbo = VBO(planeVertexData, sizeof(planeVertexData));
    ibo = IBO(planeIndexData, sizeof(planeIndexData));

    vbo.bind();
    vao = VAO(layout, 2);
}