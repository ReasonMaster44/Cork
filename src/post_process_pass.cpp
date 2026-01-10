#include <iostream>

#include "post_process_pass.h"

#include "engine/window.h"

Cork::PostProcessPass::PostProcessPass(std::string shaderFilePath, Window* window) {
    shader = Cork::Shader("../Cork/shaders/framebuffer_vert.glsl", shaderFilePath);
    framebuffer = Cork::FrameBuffer(window);

    shader.setUniformVec2("u_resolution", glm::vec2((float)window->WIN_W, (float)window->WIN_H));

    texture.loadFromFrameBuffer(&framebuffer, window);
}