#include <tuple>
#include <vector>

#include "mesh.h"

std::vector<std::tuple<int, size_t>> VertexData::getVertexDataFields() {
    return {
            {3, offsetof(VertexData, position)},
            {2, offsetof(VertexData, textureCoordinates)}
    };
}