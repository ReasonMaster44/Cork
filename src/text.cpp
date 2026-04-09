#include "text.h"

#include "opengl/texture.h"
#include "entity/quad.h"
#include "engine/overlay.h"

#include <glm/glm.hpp>

#include <iostream>

#include <algorithm>

Cork::Text::Text(FontAtlas* fontAtlas, std::string _text, glm::vec2 pos, glm::vec2 textSize) 
        : fontAtlas(fontAtlas), text(_text), pos(pos), textSize(textSize) {

    std::vector<int> indices = fontAtlas->getIndicesFromString(_text);
    
    float yOffset = 0.0f;
    float xOffset = 0.0f;

    for (int i = 0; i < indices.size(); i++) {
        if (indices[i] == -1) {
            yOffset += textSize.y * 1.5;
            xOffset = 0.0f;
        } else {
            xOffset += textSize.x;
        }

        quads.emplace_back(pos + glm::vec2(xOffset, yOffset), textSize, glm::vec3(0.0f, 0.0f, 0.0f), fontAtlas->getTexCoordsFromIndex(indices[i]));
        quads.back().addTexture(&fontAtlas->texture);
    }
}

void Cork::Text::setText(std::string newText) {
    text = newText;

    std::vector<int> indices = fontAtlas->getIndicesFromString(newText);
    
    float yOffset = 0.0f;
    float xOffset = 0.0f;

    std::vector<Cork::Overlay*> overlays = quads.begin()->overlays;

    for (Quad& quad : quads) {
        quad.removeFromOverlays();
    }

    quads.clear();

    for (int i = 0; i < indices.size(); i++) {
        if (indices[i] == -1) {
            yOffset += textSize.y * 1.5;
            xOffset = 0.0f;
        } else {
            xOffset += textSize.x;
        }

        quads.emplace_back(pos + glm::vec2(xOffset, yOffset), textSize, glm::vec3(0.0f, 0.0f, 0.0f), fontAtlas->getTexCoordsFromIndex(indices[i]));
        quads.back().addTexture(&fontAtlas->texture);
    }

    for (Cork::Overlay* overlay : overlays) {
        overlay->add(this);
    }
}