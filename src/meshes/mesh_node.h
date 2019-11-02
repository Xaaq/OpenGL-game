#ifndef MY_GAME_MESH_NODE_H
#define MY_GAME_MESH_NODE_H


#include <vector>
#include <bits/unique_ptr.h>

#include "mesh.h"

class MeshNode : public Renderable {
public:
    explicit MeshNode(std::vector<std::unique_ptr<Renderable>> &&renderables);

    void render(const ShaderProgram &shaderProgram) const override;

private:
    const std::vector<std::unique_ptr<Renderable>> renderables;
};


#endif // MY_GAME_MESH_NODE_H
