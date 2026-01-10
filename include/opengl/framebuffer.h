#pragma once

#include "opengl/shader.h"
#include "opengl/glerrorhandler.h"

#include "engine/window.h"

namespace Cork {

struct FrameBuffer {
    unsigned int fbo;
    //unsigned int texture;
    unsigned int rbo;

    static void bindDefault();

    FrameBuffer();
    FrameBuffer(Cork::Window* window);
    
    void bind();

    unsigned int getTexture();

    void setTextureUniform(const std::string& name, unsigned int _texture);

    /*
    void render() {
		shader.bind();
        va.bind();
        ib.bind();
		//GLCall(glDisable(GL_DEPTH_TEST)); // prevents framebuffer rectangle from being discarded
		GLCall(glBindTexture(GL_TEXTURE_2D, texture));
        GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
    }
    */
};

}
