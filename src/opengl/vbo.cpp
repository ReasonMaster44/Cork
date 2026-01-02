#include "opengl/vbo.h"
#include "opengl/glerrorhandler.h"

Cork::VBO::VBO() {};

Cork::VBO::VBO(float* data, unsigned int size) {
    GLCall(glGenBuffers(1, &id));
    bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Cork::VBO::bind() {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}