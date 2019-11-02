#include <string>
#include <stdexcept>

#include <stb_image.h>
#include <glad/glad.h>

#include "texture.h"

Texture::Texture(const std::string &textureName) {
    this->textureId = this->createTexture();
    this->loadImage(textureName);
}

void Texture::bindTexture(GLenum textureNumber) const {
    glActiveTexture(textureNumber);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
}

void Texture::loadImage(const std::string &textureName) const {
    std::string texturesDirectoryPath{"assets/textures/"};
    std::string texturePath{texturesDirectoryPath + textureName};

    int width, height, numberOfChannels;
    auto data = stbi_load(texturePath.c_str(), &width, &height, &numberOfChannels, 0);

    if (data == nullptr)
        throw std::runtime_error{"Couldn't load texture - " + texturePath};

    glBindTexture(GL_TEXTURE_2D, this->textureId);

    auto textureFormat = this->getTextureFormat(numberOfChannels);
    glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, static_cast<GLenum>(textureFormat),
                 GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

unsigned int Texture::createTexture() const {
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return id;
}

unsigned int Texture::getTextureFormat(int numberOfChannels) const {
    switch (numberOfChannels) {
        case 1:
            return GL_RED;
        case 2:
            return GL_RG;
        case 3:
            return GL_RGB;
        case 4:
            return GL_RGBA;
        default:
            return GL_RGB;
    }
}
