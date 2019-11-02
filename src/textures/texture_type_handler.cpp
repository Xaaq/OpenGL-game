#include <map>
#include <iostream>

#include <assimp/material.h>

#include "texture_type_handler.h"

TextureTypeHandler::TextureTypeHandler() : textureTypeMap(this->createTextureTypeMap()) {
}

const TextureTypeHandler &TextureTypeHandler::getInstance() {
    static TextureTypeHandler instance;
    return instance;
}

const std::map<aiTextureType, std::string> &TextureTypeHandler::getTextureTypeMap() const {
    return textureTypeMap;
}

std::vector<aiTextureType> TextureTypeHandler::getTextureTypes() const {
    std::vector<aiTextureType> outputVector;

    std::transform(this->textureTypeMap.begin(), this->textureTypeMap.end(), std::back_inserter(outputVector),
                   [](auto &elementPair) -> auto {
                       return elementPair.first;
                   });

    return outputVector;
}

std::map<aiTextureType, std::string> TextureTypeHandler::createTextureTypeMap() const {
    return {
            {aiTextureType_DIFFUSE,      "diffuseTexture"},
            {aiTextureType_SPECULAR,     "specularTexture"},
            {aiTextureType_AMBIENT,      "ambientTexture"},
            {aiTextureType_EMISSIVE,     "emissiveTexture"},
            {aiTextureType_HEIGHT,       "heightTexture"},
            {aiTextureType_NORMALS,      "normalsTexture"},
            {aiTextureType_SHININESS,    "shininessTexture"},
            {aiTextureType_OPACITY,      "opacityTexture"},
            {aiTextureType_DISPLACEMENT, "displacementTexture"},
            {aiTextureType_LIGHTMAP,     "lightmapTexture"},
            {aiTextureType_REFLECTION,   "reflectionTexture"}
    };
}
