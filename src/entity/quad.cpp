#include "entity/quad.h"

#include "opengl/vbo.h"
#include "opengl/ibo.h"
#include "opengl/vao.h"
#include "opengl/texture.h"
#include "opengl/shader.h"

#include "engine/overlay.h"

#include <iostream>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>


unsigned int quadIndexData[] = {
    0, 1, 2,
    1, 3, 2
};

Cork::Quad::Quad() {}

Cork::Quad::~Quad() {
    removeFromOverlays();
}

Cork::Quad::Quad(glm::vec2 pos, glm::vec2 scale, glm::vec3 colour, std::vector<float> texCoords) 
    : pos(pos), scale(scale), colour(colour) {
        
    unsigned int layout[] = {2, 2};

    float quadVertexData[] = {
        // Positions:   // Texture coords:
        0.0f, 1.0f,     texCoords[0], texCoords[1],
        1.0f, 1.0f,     texCoords[2], texCoords[3],
        0.0f, 0.0f,     texCoords[4], texCoords[5],
        1.0f, 0.0f,     texCoords[6], texCoords[7]
    };

    vbo = VBO(quadVertexData, sizeof(quadVertexData));
    ibo = IBO(quadIndexData, sizeof(quadIndexData));

    vbo.bind();
    vao = VAO(layout, 2);

    updateModel();
}

void Cork::Quad::addTexture(Texture* _texture) {
    texture = _texture;
}

void Cork::Quad::move(glm::vec2 offset) {
    pos += offset;
    updateModel();
}

void Cork::Quad::setPos(glm::vec2 newPos) {
    pos = newPos;
    updateModel();
}

void Cork::Quad::rotate(float _rotation) {
    rotation += _rotation;
    updateModel();
}

void Cork::Quad::updateModel() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.0f));
    model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(scale, 1.0f));
}

void Cork::Quad::removeFromOverlays() {
    for (Overlay* overlay : overlays) {
        overlay->remove(this);
    }
}

void Cork::Quad::removeFromOverlay(Cork::Overlay* overlay) {
    overlays.erase(std::remove(overlays.begin(), overlays.end(), overlay), overlays.end());
}