#ifndef MY_GAME_MESH_H
#define MY_GAME_MESH_H


#include <map>

#include "shaders/shader_program.h"
#include "textures/texture.h"
#include "vertex_data.h"
#include "renderable.h"

class Mesh : public Renderable {
public:
    Mesh(const std::vector<VertexData> &vertices, const std::vector<unsigned int> &faceIndices,
         std::map<aiTextureType, Texture> textures);

    void render(const ShaderProgram &shaderProgram) const override;

private:
    const int faceIndicesCount;
    unsigned int vertexBufferId{};
    unsigned int vertexArrayId{};
    unsigned int elementBufferId{};
    std::map<aiTextureType, Texture> textures;

    void createVertexBuffer(const std::vector<VertexData> &vertices) const;

    void createElementBuffer(const std::vector<unsigned int> &faceIndices) const;

    void bindTexturesToShader(const ShaderProgram &shaderProgram) const;
};


#endif // MY_GAME_MESH_H
