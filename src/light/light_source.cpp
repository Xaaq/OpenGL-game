#include <bits/unique_ptr.h>

#include "world_object.h"
#include "light_source.h"

LightSource::LightSource(std::unique_ptr<WorldObject> gameObject, const glm::vec3 &position, const glm::vec3 &color)
        : position(position), color(color), gameObject(std::move(gameObject)) {
}

void LightSource::shineLight(const ShaderProgram &shaderProgram) const {
    shaderProgram.setVec3("ambientLightColor", this->color);
}

void LightSource::render(const ShaderProgram &shaderProgram) const {
    this->gameObject->setPosition(this->position);
    this->gameObject->render(shaderProgram);
}
