#pragma once

#include "post_process_pass.h"
#include "engine/window.h"

namespace Cork {

struct PostProcessingChain {
    std::vector<PostProcessPass> passes;
    
    Cork::Window* window;

    PostProcessingChain();

    PostProcessingChain(Cork::Window* window);

    void addPass(std::string shaderFilePath);

    void update(int timeElapsed);
};
}