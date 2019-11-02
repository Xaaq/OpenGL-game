#include <bits/unique_ptr.h>

#include "mesh_node.h"

MeshNode::MeshNode(std::vector<std::unique_ptr<Renderable>> &&renderables) : renderables(std::move(renderables)) {
}

void MeshNode::render(const ShaderProgram &shaderProgram) const {
    for (const auto &renderable : this->renderables)
        renderable->render(shaderProgram);
}
