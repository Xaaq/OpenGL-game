#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "single_shader.h"

SingleShader::SingleShader(const std::string &shaderPath, GLenum shaderType) {
    auto shaderCode = this->loadCodeFromFile(shaderPath);
    this->shaderId = this->createShader(shaderCode, shaderType);
}

SingleShader::~SingleShader() {
    glDeleteShader(this->getShaderId());
}

std::string SingleShader::loadCodeFromFile(const std::string &shaderPath) const {
    std::ifstream shaderFile;
    shaderFile.open(shaderPath);

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();

    shaderFile.close();
    return shaderStream.str();
}

unsigned int SingleShader::createShader(const std::string &shaderCode, GLenum shaderType) const {
    auto shaderCodeCharArray = shaderCode.c_str();

    auto id = glCreateShader(shaderType);
    glShaderSource(id, 1, &shaderCodeCharArray, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(id, 1024, nullptr, infoLog);
        throw std::runtime_error{std::string{"Shader compilation failed - "} + infoLog};
    }

    return id;
}

unsigned int SingleShader::getShaderId() const {
    return shaderId;
}
