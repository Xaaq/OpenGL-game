#ifndef MY_GAME_SHADER_FACTORY_H
#define MY_GAME_SHADER_FACTORY_H


#include "shader_program.h"

class ShaderFactory {
public:
    ShaderProgram createShaderProgram(const std::string &shaderName) const;
};


#endif // MY_GAME_SHADER_FACTORY_H
