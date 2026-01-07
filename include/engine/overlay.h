#pragma once

#include "engine/window.h"

#include "opengl/shader.h"
#include "opengl/texture.h"

#include "entity/quad.h"
#include "text.h"

#include "glm/glm.hpp"
#include <vector>

namespace Cork {

struct Overlay {
    Shader basicShader;
    Shader textureShader;

    Shader* currentShader;

    glm::mat4 projection;
    
    std::vector<Quad*> quads;

    Overlay(Window* window);

    void add(Quad* newQuad);

    void add(Text* text);

    void setShader(Cork::Shader* newShader);

    void startFrame();

    void useTexture(Texture* texture, int index);
};

}