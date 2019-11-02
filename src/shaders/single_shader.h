#ifndef MY_GAME_SINGLE_SHADER_H
#define MY_GAME_SINGLE_SHADER_H


class SingleShader {
public:
    SingleShader(const std::string &shaderPath, GLenum shaderType);

    virtual ~SingleShader();

    [[nodiscard]] unsigned int getShaderId() const;

private:
    unsigned int shaderId;

    [[nodiscard]] std::string loadCodeFromFile(const std::string &shaderPath) const;

    [[nodiscard]] unsigned int createShader(const std::string &shaderCode, GLenum shaderType) const;
};


#endif // MY_GAME_SINGLE_SHADER_H
