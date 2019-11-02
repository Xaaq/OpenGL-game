#ifndef MY_GAME_TEXTURE_H
#define MY_GAME_TEXTURE_H


#include <string>
#include <map>

#include <glad/glad.h>
#include <assimp/material.h>

class Texture {
public:
    explicit Texture(const std::string &textureName);

    void bindTexture(GLenum textureNumber) const;

private:
    unsigned int textureId;

    void loadImage(const std::string &textureName) const;

    [[nodiscard]] unsigned int createTexture() const;

    [[nodiscard]] unsigned int getTextureFormat(int numberOfChannels) const;
};


#endif // MY_GAME_TEXTURE_H
