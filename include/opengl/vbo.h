#pragma once

namespace Cork {

struct VBO {
    unsigned int id;

    VBO();

    VBO(float* data, unsigned int size);

    void bind();
};

}