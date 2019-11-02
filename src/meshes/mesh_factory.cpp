#include <vector>
#include <iostream>
#include <bits/unique_ptr.h>
#include <map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh_factory.h"
#include "textures/texture_type_handler.h"
#include "mesh_node.h"

std::unique_ptr<Renderable> MeshFactory::loadMesh(const std::string &modelName) const {
    std::string modelDirectoryPath{"assets/models/"};
    std::string modelPath{modelDirectoryPath + modelName};

    Assimp::Importer importer;
    const auto scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
        throw std::runtime_error{std::string{"Mesh loading error - "} + importer.GetErrorString()};

    auto processedNodes = this->processNode(scene->mRootNode, scene);
    return processedNodes;
}

std::unique_ptr<MeshNode> MeshFactory::processNode(const aiNode *node, const aiScene *scene) const {
    std::vector<std::unique_ptr<Renderable>> renderableVector{};

    for (int i = 0; i < node->mNumMeshes; i++) {
        const auto meshIndex = node->mMeshes[i];
        const auto mesh = scene->mMeshes[meshIndex];
        auto processedMesh = this->processMesh(mesh, scene);
        renderableVector.push_back(std::move(processedMesh));
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        auto processedNode = this->processNode(node->mChildren[i], scene);
        renderableVector.push_back(std::move(processedNode));
    }

    auto meshNode = std::make_unique<MeshNode>(std::move(renderableVector));
    return meshNode;
}

std::unique_ptr<Mesh> MeshFactory::processMesh(const aiMesh *mesh, const aiScene *scene) const {
    auto vertices = extractVertexData(mesh);
    auto faceIndices = extractFaceIndices(mesh);

    auto material = scene->mMaterials[mesh->mMaterialIndex];
    auto textures = this->loadMaterialTextures(material);

    auto outputMesh = std::make_unique<Mesh>(vertices, faceIndices, textures);
    return outputMesh;
}

std::vector<VertexData> MeshFactory::extractVertexData(const aiMesh *mesh) const {
    std::vector<VertexData> vertices;

    for (auto i = 0; i < mesh->mNumVertices; ++i) {
        auto currentVertex = mesh->mVertices[i];

        VertexData vertexData{};
        vertexData.position = glm::vec3{currentVertex.x, currentVertex.y, currentVertex.z};

        const auto textureCoordinatesArray = mesh->mTextureCoords[0];

        if (textureCoordinatesArray != nullptr) {
            const auto currentTextureCoordinates = textureCoordinatesArray[i];
            vertexData.textureCoordinates = glm::vec2{currentTextureCoordinates.x, currentTextureCoordinates.y};
        }

        vertices.push_back(vertexData);
    }

    return vertices;
}

std::vector<unsigned int> MeshFactory::extractFaceIndices(const aiMesh *mesh) const {
    std::vector<unsigned int> faceIndices;

    for (auto i = 0; i < mesh->mNumFaces; ++i) {
        auto currentFace = mesh->mFaces[i];

        for (auto j = 0u; j < currentFace.mNumIndices; ++j) {
            auto currentIndex = currentFace.mIndices[j];
            faceIndices.push_back(currentIndex);
        }
    }

    return faceIndices;
}

std::map<aiTextureType, Texture> MeshFactory::loadMaterialTextures(aiMaterial *material) const {
    std::map<aiTextureType, Texture> textures;
    auto &textureTypeHandler = TextureTypeHandler::getInstance();

    for (const auto &textureType : textureTypeHandler.getTextureTypes()) {
        aiString filePath;
        auto result = material->GetTexture(textureType, 0, &filePath);

        if (result >= 0) {
            Texture texture{filePath.C_Str()};
            textures.insert({textureType, texture});
        }
    }

    return textures;
}
