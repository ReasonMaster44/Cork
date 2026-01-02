#include "opengl/vao.h"
#include "opengl/glerrorhandler.h"

Cork::VAO::VAO() {};

Cork::VAO::VAO(unsigned int* layout, unsigned int numberOfVertAttributes) {
    GLCall(glGenVertexArrays(1, &id));
    bind();

    unsigned int stride = 0;
    for (unsigned int i = 0; i < numberOfVertAttributes; i++) {
        stride += layout[i];
    }

    stride *= sizeof(float);

    unsigned int pointer = 0;
    for (unsigned int i = 0; i < numberOfVertAttributes; i++) {
        if (i > 0) {
            pointer = layout[i - 1];
        }
        GLCall(glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE, stride, (void*)(pointer * sizeof(float))));
        GLCall(glEnableVertexAttribArray(i));
    }
}

void Cork::VAO::bind() {
    GLCall(glBindVertexArray(id));
}