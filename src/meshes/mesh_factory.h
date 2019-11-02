#ifndef MY_GAME_MESH_FACTORY_H
#define MY_GAME_MESH_FACTORY_H


#include <string>
#include <bits/unique_ptr.h>

#include <assimp/scene.h>

#include "mesh.h"
#include "textures/texture.h"
#include "mesh_node.h"

class MeshFactory {
public:
    [[nodiscard]] std::unique_ptr<Renderable> loadMesh(const std::string &modelName) const;

private:
    std::unique_ptr<MeshNode> processNode(const aiNode *node, const aiScene *scene) const;

    std::unique_ptr<Mesh> processMesh(const aiMesh *mesh, const aiScene *scene) const;

    std::vector<VertexData> extractVertexData(const aiMesh *mesh) const;

    std::vector<unsigned int> extractFaceIndices(const aiMesh *mesh) const;

    std::map<aiTextureType, Texture> loadMaterialTextures(aiMaterial *material) const;
};


#endif // MY_GAME_MESH_FACTORY_H
