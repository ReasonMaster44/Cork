#include <iostream>
#include <fstream>

#include "opengl/shader.h"
#include "opengl/glerrorhandler.h"

#include <glm/gtc/type_ptr.hpp>

#include "glad/glad.h"

Cork::Shader::Shader() {}

Cork::Shader::Shader(std::string vertSourceCodePath, std::string fragSourceCodePath) {
    std::string vertSourceCode = parseShaderFile(vertSourceCodePath);
    const char* vertSourceCodeCstr = vertSourceCode.c_str();

    std::string fragSourceCode = parseShaderFile(fragSourceCodePath);
    const char* fragSourceCodeCstr = fragSourceCode.c_str();

    unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLCall(glShaderSource(vertShader, 1, &vertSourceCodeCstr, nullptr));
    GLCall(glCompileShader(vertShader));

    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLCall(glShaderSource(fragShader, 1, &fragSourceCodeCstr, nullptr));
    GLCall(glCompileShader(fragShader));

    // Check for compilation errors
    int success;
    char infoLog[512];
    
    GLCall(glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLCall(glGetShaderInfoLog(vertShader, 512, nullptr, infoLog));
        std::cerr << "Failed to compile vertex shader:\n" << infoLog << std::endl;
    }

    GLCall(glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLCall(glGetShaderInfoLog(fragShader, 512, nullptr, infoLog));
        std::cerr << "Failed to compile fragment shader:\n" << infoLog << std::endl;
    }
    
    ID = glCreateProgram();
    GLCall(glAttachShader(ID, vertShader));
    GLCall(glAttachShader(ID, fragShader));
    GLCall(glLinkProgram(ID));

    // Check for linking errors
    GLCall(glGetProgramiv(ID, GL_LINK_STATUS, &success));
    if (!success) {
        GLCall(glGetProgramInfoLog(ID, 512, nullptr, infoLog));
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
    }

    GLCall(glDeleteShader(vertShader));
    GLCall(glDeleteShader(fragShader));
}

void Cork::Shader::bind() {
    GLCall(glUseProgram(ID));
}

void Cork::Shader::unbind() {
    GLCall(glUseProgram(0));
}

void Cork::Shader::setUniformMat4(std::string name, glm::mat4 matrix) {
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

void Cork::Shader::setUniformVec3(std::string name, glm::vec3 vector) {
    GLCall(glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z));
}

void Cork::Shader::setUniform1i(std::string name, int value) {
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Cork::Shader::setUniformVec2(std::string name, glm::vec2 vector) {
    GLCall(glUniform2f(getUniformLocation(name), vector.x, vector.y));
}

void Cork::Shader::setUniform1f(std::string name, float value) {
    GLCall(glUniform1f(getUniformLocation(name), value));
}

int Cork::Shader::getUniformLocation(std::string name) {
    bind();
    const char* nameCstring = name.c_str();
    int location = glGetUniformLocation(ID, nameCstring);

    if (location == -1) {
        std::cerr << "Uniform " << name << " either does not exist or is not used in the shader." << std::endl;
        return -1;
    } else {
        return location;
    }
}
