#pragma once

#include <string>

namespace Cork {

class Texture {
private:
    unsigned int m_rendererID;
    std::string m_filepath;
    unsigned char* m_localBuffer;
    int m_width, m_height, m_bitsPerPixel;

public:

    Texture();
    Texture(const std::string& filepath);

    ~Texture();
    
    void bind(unsigned int slot = 0) const;

    void unbind();

    inline int getWidth() const;
    inline int getHeight() const;
};

}