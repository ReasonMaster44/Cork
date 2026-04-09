#pragma once

#include <string>
#include "opengl/texture.h"

#include <glm/glm.hpp>

namespace Cork {

struct FontAtlas {
    Texture texture;
    
    glm::ivec2 fontAtlasSize;
    glm::ivec2 glyphSize;
    std::vector<char> glyphOrder;

    FontAtlas(std::string fontAtlasPath, glm::ivec2 fontAtlasSize, glm::ivec2 glyphSize, std::vector<char> glyphOrder);

    std::vector<float> getTexCoordsFromIndex(int index);

    std::vector<int> getIndicesFromString(std::string text);
};

}