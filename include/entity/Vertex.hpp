#pragma once

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

struct Vertex {
    float pos[3];

    glm::vec3 pos_vec3() const { return glm::vec3(pos[0], pos[1], pos[2]); }
    Vertex transformed(glm::mat4 model) const {
        glm::vec4 posvec = model * glm::vec4(pos_vec3(), 1.0f);

        return {posvec[0] / posvec[3], posvec[1] / posvec[3],
                posvec[2] / posvec[3]};
    }
};

struct ColorVertex : public Vertex {
    float color[4];
};

}  // namespace Engine