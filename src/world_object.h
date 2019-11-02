#ifndef MY_GAME_WORLD_OBJECT_H
#define MY_GAME_WORLD_OBJECT_H


#include <memory>
#include <bits/unique_ptr.h>
#include <bits/shared_ptr.h>

#include <glm/vec3.hpp>

#include "meshes/renderable.h"

class WorldObject {
public:
    explicit WorldObject(std::shared_ptr<Renderable> renderable);

    void render(const ShaderProgram &shaderProgram) const;

    void setPosition(const glm::vec3 &position);

private:
    glm::vec3 position{0};
    std::shared_ptr<Renderable> renderable;
};


#endif // MY_GAME_WORLD_OBJECT_H
