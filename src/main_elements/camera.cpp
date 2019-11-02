#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

Camera::Camera(const float fieldOfView, const float aspectRatio) {
    glm::mat4 tempViewMatrix{1.0f};
    this->viewMatrix = glm::translate(tempViewMatrix, glm::vec3(0, 0, -5));
    this->projectionMatrix = glm::perspective(fieldOfView, aspectRatio, 0.1f, 100.0f);
}

void Camera::updateShader(const ShaderProgram &shaderProgram) const {
    shaderProgram.setMatrix("viewMatrix", this->viewMatrix);
    shaderProgram.setMatrix("projectionMatrix", this->projectionMatrix);
}
