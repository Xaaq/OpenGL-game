#ifndef MY_GAME_VERTEX_DATA_H
#define MY_GAME_VERTEX_DATA_H


#include <vector>
#include <map>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct VertexData {
    glm::vec3 position;
    glm::vec2 textureCoordinates;

    static std::vector<std::tuple<int, size_t>> getVertexDataFields();
};


#endif // MY_GAME_VERTEX_DATA_H
