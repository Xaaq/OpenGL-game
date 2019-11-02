#ifndef MY_GAME_TEXTURE_TYPE_HANDLER_H
#define MY_GAME_TEXTURE_TYPE_HANDLER_H


#include <vector>

class TextureTypeHandler {
public:
    TextureTypeHandler(const TextureTypeHandler &) = delete;

    void operator=(const TextureTypeHandler &) = delete;

    static const TextureTypeHandler &getInstance();

    [[nodiscard]] const std::map<aiTextureType, std::string> &getTextureTypeMap() const;

    [[nodiscard]] std::vector<aiTextureType> getTextureTypes() const;

private:
    TextureTypeHandler();

    const std::map<aiTextureType, std::string> textureTypeMap;

    [[nodiscard]] std::map<aiTextureType, std::string> createTextureTypeMap() const;
};


#endif // MY_GAME_TEXTURE_TYPE_HANDLER_H
