#pragma once

#include <string>
#include "opengl/texture.h"
#include "entity/quad.h"
#include "font_atlas.h"

#include <glm/glm.hpp>

namespace Cork {

struct Text {
    FontAtlas* fontAtlas;

    std::string text;

    glm::vec2 pos;
    glm::vec2 textSize;

    std::vector<Quad> quads;
    
    Text(FontAtlas* fontAtlas, std::string text, glm::vec2 pos, glm::vec2 textSize);

    void setText(std::string newText);
};

}