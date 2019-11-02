#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "world_object.h"

WorldObject::WorldObject(std::shared_ptr<Renderable> renderable) : renderable(std::move(renderable)) {
}

void WorldObject::render(const ShaderProgram &shaderProgram) const {
    glm::mat4 translationMatrix = glm::mat4(1);
    translationMatrix = glm::translate(translationMatrix, this->position);

    const auto rotation = (sin(glfwGetTime()) + 1) * 45;
    translationMatrix = glm::rotate(translationMatrix, glm::radians(static_cast<float>(rotation)),
                                    glm::vec3(1.0, 0.0, 1.0));

    shaderProgram.setMatrix("modelMatrix", translationMatrix);
    this->renderable->render(shaderProgram);
}

void WorldObject::setPosition(const glm::vec3 &position) {
    WorldObject::position = position;
}
