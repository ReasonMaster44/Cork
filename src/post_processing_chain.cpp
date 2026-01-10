#include "post_process_pass.h"
#include "cork.h"

#include "post_processing_chain.h"


Cork::PostProcessingChain::PostProcessingChain(Cork::Window* window, std::vector<std::string> shaderFilePaths) {
    for (int i = 0; i < shaderFilePaths.size(); i++) {
        passes.emplace_back(shaderFilePaths[i], window);
    }
}