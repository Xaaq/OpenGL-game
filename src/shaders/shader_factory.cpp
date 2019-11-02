#include <glad/glad.h>

#include "shader_factory.h"
#include "single_shader.h"

ShaderProgram ShaderFactory::createShaderProgram(const std::string &shaderName) const {
    std::string shaderDirectoryPath{"assets/shaders/"};
    std::string basicVertexShaderPath{shaderDirectoryPath + shaderName + ".vert"};
    std::string basicFragmentShaderPath{shaderDirectoryPath + shaderName + ".frag"};

    SingleShader vertexShaderLoader{basicVertexShaderPath, GL_VERTEX_SHADER};
    SingleShader fragmentShaderLoader{basicFragmentShaderPath, GL_FRAGMENT_SHADER};

    ShaderProgram basicShaderProgram{vertexShaderLoader.getShaderId(), fragmentShaderLoader.getShaderId()};
    return basicShaderProgram;
}
