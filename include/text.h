#pragma once

#include <string>
#include "opengl/texture.h"
#include "entity/quad.h"
#include "font_atlas.h"

#include <glm/glm.hpp>

namespace Cork {

struct Text {
    FontAtlas* fontAtlas;

    glm::vec2 textSize;
    glm::vec2 pos;

    std::string text;

    std::vector<Quad> quads;
    
    Text(FontAtlas* fontAtlas, std::string text, glm::vec2 pos, glm::vec2 size);

    void setText(std::string newText);
};

}