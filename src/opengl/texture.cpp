#include "opengl/texture.h"
#include "opengl/glerrorhandler.h"
#include "opengl/framebuffer.h"

#include "engine/window.h"

#include <iostream>

#include "stb_image/stb_image.h"

Cork::Texture::Texture() 
    : m_width(0), m_height(0), m_bitsPerPixel(0) {
    
    GLCall(glGenTextures(1, &id));
    GLCall(glBindTexture(GL_TEXTURE_2D, id));
        
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    
    unbind();
}

void Cork::Texture::loadFromFile(const std::string filePath) {
    GLCall(glBindTexture(GL_TEXTURE_2D, id));
    
    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

    unbind();
    if (m_localBuffer) {
        stbi_image_free(m_localBuffer);
    }
}

void Cork::Texture::loadFromFrameBuffer(Cork::FrameBuffer* framebuffer, Cork::Window* window) {
    bind();
    framebuffer->bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, window->frameBufferWidth, window->frameBufferHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);

    Cork::FrameBuffer::bindDefault();
    unbind();
}

Cork::Texture::~Texture() {
    GLCall(glDeleteTextures(1, &id));
}

void Cork::Texture::bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, id));
}

void Cork::Texture::unbind() {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

inline int Cork::Texture::getWidth() const { return m_width; }
inline int Cork::Texture::getHeight() const { return m_height; }