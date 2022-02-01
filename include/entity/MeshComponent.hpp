#pragma once

#include "Vertex.hpp"

namespace Engine {

struct MeshComponent {
    Vertex* vertices;
    unsigned int* indices;
    unsigned int vertex_count;
    unsigned int index_count;
};

}  // namespace Engine