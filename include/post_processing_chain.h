#include "post_process_pass.h"

namespace Cork {

struct PostProcessingChain {
    std::vector<PostProcessPass> passes;

    PostProcessingChain(Cork::Window* window, std::vector<std::string> shaderFilePaths);


};
}