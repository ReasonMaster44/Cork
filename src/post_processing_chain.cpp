#include "post_process_pass.h"
#include "cork.h"

#include "post_processing_chain.h"

Cork::PostProcessingChain::PostProcessingChain() {}

Cork::PostProcessingChain::PostProcessingChain(Cork::Window* window) 
    : window(window) {
    passes.reserve(10);
}

void Cork::PostProcessingChain::addPass(std::string shaderFilePath) {
    passes.emplace_back(shaderFilePath, window);
}

void Cork::PostProcessingChain::update(int timeElapsed) {
    for (int i = 0; i < passes.size(); i++) {
        passes[i].update(timeElapsed);
    }
}