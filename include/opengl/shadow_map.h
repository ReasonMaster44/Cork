#pragma once

namespace Cork {

struct ShadowMap {
    unsigned int fbo;
    unsigned int width, height;
    unsigned int texture;

    ShadowMap();

    ShadowMap(unsigned int width, unsigned int height);

    void bindFramebuffer();

    void bindTexture();

    void bindForRendering();

    void unbind(unsigned int frameBufferWidth, unsigned int frameBufferHeight);
};

}