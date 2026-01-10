#pragma once

#include <string>

#include "engine/window.h"
#include "opengl/framebuffer.h"

namespace Cork {

struct Texture {
    unsigned int id;

    unsigned char* m_localBuffer = nullptr;
    int m_width, m_height, m_bitsPerPixel;


    Texture();
    ~Texture();
    
    void bind(unsigned int slot = 0) const;
    void unbind();

    void loadFromFile(const std::string filePath);
    void loadFromFrameBuffer(Cork::FrameBuffer* framebuffer, Cork::Window* window);

    inline int getWidth() const;
    inline int getHeight() const;
};

}