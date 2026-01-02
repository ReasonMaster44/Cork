#pragma once

#include <string>
#include "opengl/texture.h"
#include "entity/quad.h"

#include <glm/glm.hpp>

namespace Cork {

struct Text {
    Texture fontAtlas;

    std::vector<Quad> quads;

    Text(std::string fontAtlasPath, std::string text, glm::vec2 pos, glm::vec2 scale);
};

}