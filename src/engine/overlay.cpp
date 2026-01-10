#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "opengl/shader.h"
#include "opengl/texture.h"

#include "engine/overlay.h"
#include "engine/window.h"

#include "entity/quad.h"

#include "camera.h"
#include "text.h"


Cork::Overlay::Overlay(Window* window) {
    basicShader = Shader("../Cork/shaders/overlay_vert.glsl", "../Cork/shaders/overlay_frag.glsl");
    textureShader = Shader("../Cork/shaders/overlay_vert.glsl", "../Cork/shaders/overlay_frag_tex.glsl");

    currentShader = &basicShader;

    projection = glm::ortho(0.0f, (float)window->WIN_W, (float)window->WIN_H, 0.0f, -1.0f, 1.0f);
}

void Cork::Overlay::add(Quad* newQuad) {
    quads.push_back(newQuad);
}

void Cork::Overlay::setShader(Shader* shader) {
    currentShader = shader;
}

void Cork::Overlay::add(Text* text) {
    for (Quad& quad : text->quads) {
        add(&quad);
    }
}

void Cork::Overlay::startFrame() {
    //basicShader.bind();
    //basicShader.setUniformMat4("u_projection", projection);

    //textureShader.bind();
    //textureShader.setUniformMat4("u_projection", projection);
    currentShader->bind();
    currentShader->setUniformMat4("u_projection", projection);
}

void Cork::Overlay::useTexture() {
    currentShader = &textureShader;
}