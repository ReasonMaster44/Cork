#pragma once

namespace Cork {

struct IBO {
    unsigned int id;
    unsigned int count;

    IBO();

    IBO(unsigned int* data, unsigned int size);

    void bind();
};

}