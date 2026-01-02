#include "opengl/texture.h"
#include "opengl/glerrorhandler.h"

#include <iostream>

#include "stb_image/stb_image.h"

Cork::Texture::Texture() {}

Cork::Texture::Texture(const std::string& filepath) 
: m_filepath(filepath), m_localBuffer(nullptr), 
    m_width(0), m_height(0), m_bitsPerPixel(0) {
    
    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);

    GLCall(glGenTextures(1, &m_rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_localBuffer) {
        stbi_image_free(m_localBuffer);
    }
}

Cork::Texture::~Texture() {
    GLCall(glDeleteTextures(1, &m_rendererID));
}

void Cork::Texture::bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Cork::Texture::unbind() {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

inline int Cork::Texture::getWidth() const { return m_width; }
inline int Cork::Texture::getHeight() const { return m_height; }