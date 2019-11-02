#ifndef MY_GAME_CAMERA_H
#define MY_GAME_CAMERA_H


#include <glm/glm.hpp>

#include "shaders/shader_program.h"

class Camera {
public:
    Camera(float fieldOfView, float aspectRatio);

    void updateShader(const ShaderProgram &shaderProgram) const;

private:
    glm::mat4 projectionMatrix{};
    glm::mat4 viewMatrix{};
};


#endif // MY_GAME_CAMERA_H
