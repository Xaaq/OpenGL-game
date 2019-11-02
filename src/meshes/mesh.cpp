#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include <map>

#include <glad/glad.h>
#include <assimp/material.h>

#include "mesh.h"
#include "textures/texture_type_handler.h"

Mesh::Mesh(const std::vector<VertexData> &vertices, const std::vector<unsigned int> &faceIndices,
           std::map<aiTextureType, Texture> textures) :
        faceIndicesCount(static_cast<const int>(faceIndices.size())),
        textures(std::move(textures)) {
    glGenVertexArrays(1, &this->vertexArrayId);
    glGenBuffers(1, &this->vertexBufferId);
    glGenBuffers(1, &this->elementBufferId);

    this->createVertexBuffer(vertices);
    this->createElementBuffer(faceIndices);
}

void Mesh::render(const ShaderProgram &shaderProgram) const {
    this->bindTexturesToShader(shaderProgram);

    shaderProgram.useProgram();
    glBindVertexArray(this->vertexArrayId);
    glDrawElements(GL_TRIANGLES, this->faceIndicesCount, GL_UNSIGNED_INT, nullptr);
}

void Mesh::createVertexBuffer(const std::vector<VertexData> &vertices) const {
    glBindVertexArray(this->vertexArrayId);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    auto vertexDataList = VertexData::getVertexDataFields();

    for (auto index = 0ul; index < vertexDataList.size(); ++index) {
        auto vertexData = vertexDataList[index];
        auto fieldSize = std::get<0>(vertexData);
        auto fieldOffset = std::get<1>(vertexData);

        glVertexAttribPointer(index, fieldSize, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                              reinterpret_cast<void *>(fieldOffset));
        glEnableVertexAttribArray(index);
    }
}

void Mesh::createElementBuffer(const std::vector<unsigned int> &faceIndices) const {
    glBindVertexArray(this->vertexArrayId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * faceIndices.size(), faceIndices.data(),
                 GL_STATIC_DRAW);
}

void Mesh::bindTexturesToShader(const ShaderProgram &shaderProgram) const {
    shaderProgram.useProgram();
    const auto textureMap = TextureTypeHandler::getInstance().getTextureTypeMap();

    for (auto[textureNumber, texturePair] = std::make_tuple(0, textureMap.begin());
         texturePair != textureMap.end();
         ++textureNumber, ++texturePair) {
        const auto textureType = texturePair->first;
        const auto textureShaderName = texturePair->second;

        shaderProgram.setInt(textureShaderName, textureNumber);
        const auto diffuseTexture = this->textures.find(textureType)->second;
        diffuseTexture.bindTexture(static_cast<GLenum>(GL_TEXTURE0 + textureNumber));

        ++textureNumber;
    }
}
