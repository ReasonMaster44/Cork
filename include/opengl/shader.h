#pragma once

#include <fstream>
#include "glm/glm.hpp"

inline std::string parseShaderFile(std::string filePath) {
    std::ifstream file(filePath);
    std::string sourceCode;
    std::string line;

    while (std::getline(file, line)) {
        sourceCode += line + "\n";
    }

    return sourceCode;
}

namespace Cork {

struct Shader {
    unsigned int ID;

    Shader();

    Shader(std::string vertSourceCodePath, std::string fragSourceCodePath);

    void bind();

    void setUniformMat4(std::string name, glm::mat4 matrix);

    void setUniformVec3(std::string name, glm::vec3 vector);

    void setUniform1i(std::string name, int value);

    int getUniformLocation(std::string name);
};

}