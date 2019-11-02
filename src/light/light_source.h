#ifndef MY_GAME_LIGHT_SOURCE_H
#define MY_GAME_LIGHT_SOURCE_H


#include <bits/unique_ptr.h>

#include <glm/vec3.hpp>

#include "shaders/shader_program.h"

class LightSource {
public:
    LightSource(std::unique_ptr<WorldObject> gameObject, const glm::vec3 &position, const glm::vec3 &color);

    void render(const ShaderProgram &shaderProgram) const;

    void shineLight(const ShaderProgram &shaderProgram) const;

private:
    std::unique_ptr<WorldObject> gameObject;
    glm::vec3 position;
    glm::vec3 color;
};


#endif // MY_GAME_LIGHT_SOURCE_H
