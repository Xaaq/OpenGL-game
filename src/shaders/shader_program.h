#ifndef MY_GAME_SHADER_PROGRAM_H
#define MY_GAME_SHADER_PROGRAM_H


#include <string>

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>

class ShaderProgram {
public:
    ShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId);

    void useProgram() const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVec3(const std::string &name, const glm::vec3 &inputVector) const;

    void setMatrix(const std::string &name, const glm::mat4 &inputMatrix) const;

private:
    const unsigned int shaderProgramId;

    [[nodiscard]] unsigned int createShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId) const;
};


#endif // MY_GAME_SHADER_PROGRAM_H
