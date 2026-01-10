#include <iostream>

#include "glad/glad.h"

#include "opengl/shader.h"
#include "opengl/framebuffer.h"
#include "opengl/texture.h"

#include "engine/window.h"


void Cork::FrameBuffer::bindDefault() { GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0)); }

Cork::FrameBuffer::FrameBuffer() {}

Cork::FrameBuffer::FrameBuffer(Cork::Window* window) {
    // Create Frame Buffer Object
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Create Render Buffer Object
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window->frameBufferWidth, window->frameBufferHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    FrameBuffer::bindDefault(); 
}

void Cork::FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}