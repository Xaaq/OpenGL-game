#include <stdexcept>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "shader_program.h"

ShaderProgram::ShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId) :
        shaderProgramId(this->createShaderProgram(vertexShaderId, fragmentShaderId)) {
}

unsigned int ShaderProgram::createShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId) const {
    auto programId = glCreateProgram();

    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    int linkingResult;
    glGetProgramiv(programId, GL_LINK_STATUS, &linkingResult);

    if (linkingResult == 0) {
        char infoLog[1024];
        glGetProgramInfoLog(programId, 1024, nullptr, infoLog);
        throw std::runtime_error{std::string{"Shader program linking failed - "} + infoLog};
    }

    return programId;
}

void ShaderProgram::useProgram() const {
    glUseProgram(this->shaderProgramId);
}

void ShaderProgram::setInt(const std::string &name, int value) const {
    this->useProgram();
    const auto variableLocation = glGetUniformLocation(this->shaderProgramId, name.c_str());
    glUniform1i(variableLocation, value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const {
    this->useProgram();
    const auto variableLocation = glGetUniformLocation(this->shaderProgramId, name.c_str());
    glUniform1f(variableLocation, value);
}

void ShaderProgram::setVec3(const std::string &name, const glm::vec3 &inputVector) const {
    this->useProgram();
    const auto variableLocation = glGetUniformLocation(this->shaderProgramId, name.c_str());
    glUniform3fv(variableLocation, 1, &inputVector[0]);
}

void ShaderProgram::setMatrix(const std::string &name, const glm::mat4 &inputMatrix) const {
    this->useProgram();
    const auto variableLocation = glGetUniformLocation(this->shaderProgramId, name.c_str());
    glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr(inputMatrix));
}

