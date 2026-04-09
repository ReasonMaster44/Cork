#include "font_atlas.h"

#include "opengl/texture.h"

#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>

Cork::FontAtlas::FontAtlas(std::string fontAtlasPath, glm::ivec2 fontAtlasSize, glm::ivec2 glyphSize, std::vector<char> glyphOrder) 
        : fontAtlasSize(fontAtlasSize), glyphSize(glyphSize), glyphOrder(glyphOrder) {

    texture.loadFromFile(fontAtlasPath);
}

std::vector<float> Cork::FontAtlas::getTexCoordsFromIndex(int index) {
    int glyphsPerRow = fontAtlasSize.x / glyphSize.x;
    int glyphsPerColumn = fontAtlasSize.y / glyphSize.y;
    
    int row = index / glyphsPerRow; // Which row the glyph is in
    int column = index % glyphsPerColumn; // Which column the glyph is in
    
    glm::vec2 glyphSize = glm::vec2(1.0f / glyphsPerRow, 1.0f / glyphsPerColumn);
    glm::vec2 glyphPos = glm::vec2(glyphSize.x * column, glyphSize.y * row); // Position of the target glyph relative to the font atlas

    std::vector<float> texCoords = {glyphPos.x,               glyphPos.y + glyphSize.y,
                                    glyphPos.x + glyphSize.x, glyphPos.y + glyphSize.y,
                                    glyphPos.x,               glyphPos.y,
                                    glyphPos.x + glyphSize.x, glyphPos.y};

    return texCoords;
}

std::vector<int> Cork::FontAtlas::getIndicesFromString(std::string _text) {
    std::vector<int> indices;

    for (char c : _text) {
        auto it = std::find(glyphOrder.begin(), glyphOrder.end(), c);
        int index = std::distance(glyphOrder.begin(), it);

        if (c == '\n') {
            indices.push_back(-1);
        } else {
            indices.push_back(index);
        }
    }

    return indices;
}