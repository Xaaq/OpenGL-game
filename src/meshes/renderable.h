#ifndef MY_GAME_RENDERABLE_H
#define MY_GAME_RENDERABLE_H


#include "shaders/shader_program.h"

class Renderable {
public:
    virtual void render(const ShaderProgram &shaderProgram) const = 0;
};


#endif // MY_GAME_RENDERABLE_H
