#include <iostream>

#include "entity/mesh.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Cork::Mesh::Mesh() {}

Cork::Mesh::Mesh(glm::vec3 pos, glm::vec3 scale, glm::vec3 colour)
    : Cork::Entity(pos), scale(scale), colour(colour) {
    update();
}

void Cork::Mesh::update() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = model * orientation;
    model = glm::scale(model, scale);
}

bool Cork::Mesh::rayIntersect(glm::vec3 rayOrigin, glm::vec3 rayDir) {
    glm::vec3 min = pos - scale;
    glm::vec3 max = pos + scale;

    glm::vec3 tMin = (min - rayOrigin) / rayDir;
    glm::vec3 tMax = (max - rayOrigin) / rayDir;

    glm::vec3 t1 = glm::min(tMin, tMax);
    glm::vec3 t2 = glm::max(tMin, tMax);

    float tNear = std::max(std::max(t1.x, t1.y), t1.z);
    float tFar  = std::min(std::min(t2.x, t2.y), t2.z);

    return tNear < tFar;
}

void Cork::Mesh::addTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 colour) {
    vertexPositions.push_back(a);
    vertexPositions.push_back(b);
    vertexPositions.push_back(c);

    glm::vec3 edge1 = b - a;
    glm::vec3 edge2 = c - a;

    glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));
    vertexNormals.push_back(normal);
    vertexNormals.push_back(normal);
    vertexNormals.push_back(normal);

    vertexColours.push_back(colour);
    vertexColours.push_back(colour);
    vertexColours.push_back(colour);

    unsigned int start = indices.size() == 0 ? 0 : indices.back() + 1;

    indices.push_back(start);
    indices.push_back(start + 1);
    indices.push_back(start + 2);
}

void Cork::Mesh::addFace(std::vector<glm::vec3> positions, std::vector<unsigned int> _indices, glm::vec3 colour, glm::vec3 offset) {
    glm::vec3 edge1 = positions[1] - positions[0];
    glm::vec3 edge2 = positions[2] - positions[0];

    glm::vec3 normal = glm::normalize(glm::cross(edge2, edge1));
    
    for (int i = 0; i < positions.size(); i++) {
        vertexPositions.push_back(positions[i] + offset);
        vertexNormals.push_back(normal);
        vertexColours.push_back(colour);
    }

    unsigned int start = indices.size() == 0 ? 0 : indices.back() + 1;

    for (int i = 0; i < _indices.size(); i++) {
        indices.push_back(_indices[i] + start);
    }
}

void Cork::Mesh::updateBuffers() {
    int numberOfFloats = (vertexPositions.size() * 3) + (vertexNormals.size() * 3) + (vertexColours.size() * 3);
    float _vertexData[numberOfFloats];

    float _vertex[9];

    for (int i = 0; i < numberOfFloats; i += 1) {
        int relativeI = i % 9;
        int globalI = i / 9;

        _vertex[0] = vertexPositions[globalI].x;
        _vertex[1] = vertexPositions[globalI].y;
        _vertex[2] = vertexPositions[globalI].z;

        _vertex[3] = vertexNormals[globalI].x;
        _vertex[4] = vertexNormals[globalI].y;
        _vertex[5] = vertexNormals[globalI].z;

        _vertex[6] = vertexColours[globalI].x;
        _vertex[7] = vertexColours[globalI].y;
        _vertex[8] = vertexColours[globalI].z;

        _vertexData[i] = _vertex[relativeI];
    }

    unsigned int indexData[indices.size()];

    for (int i = 0; i < indices.size(); i++) { indexData[i] = indices[i]; }
    
    vbo = VBO(_vertexData, sizeof(_vertexData));
    ibo = IBO(indexData, sizeof(indexData));
    vbo.bind();
    vao = VAO(layout, 3);
}