#pragma once

#include <iostream>

#include "opengl/shader.h"
#include "opengl/texture.h"
#include "opengl/framebuffer.h"

#include "engine/window.h"

namespace Cork {

struct PostProcessPass {
    Cork::Shader shader;
    Cork::Texture texture;
    Cork::FrameBuffer framebuffer;

    PostProcessPass(std::string shaderFilePath, Window* window);
};

}