#include "opengl/ibo.h"
#include "opengl/glerrorhandler.h"

Cork::IBO::IBO() {};

Cork::IBO::IBO(unsigned int* data, unsigned int size) {
    count = size / sizeof(unsigned int);
    
    GLCall(glGenBuffers(1, &id));
    bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void Cork::IBO::bind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}
