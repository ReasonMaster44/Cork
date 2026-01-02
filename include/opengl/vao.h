#pragma once

namespace Cork {

struct VAO {
    unsigned int id;
    
    VAO();

    VAO(unsigned int* layout, unsigned int numberOfVertAttributes);

    void bind();
};

}