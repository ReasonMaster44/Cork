#include "opengl/shadow_map.h"
#include "opengl/shader.h"

#include "glad/glad.h"

#include <iostream>

Cork::ShadowMap::ShadowMap(unsigned int width, unsigned int height) : width(width), height(height) {
    glGenFramebuffers(1, &fbo);

    glGenTextures(1, &texture);
    bindTexture();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float clampColour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColour);

    bindFramebuffer();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "ERROR: Shadow map framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Cork::ShadowMap::bindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Cork::ShadowMap::bindTexture() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Cork::ShadowMap::bindForRendering() {
    glViewport(0, 0, width, height);
    glCullFace(GL_FRONT);
    
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.1f, 4.0f);
}

void Cork::ShadowMap::unbind(unsigned int frameBufferWidth, unsigned int frameBufferHeight) {
    glDisable(GL_POLYGON_OFFSET_FILL);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    glCullFace(GL_BACK);
}
