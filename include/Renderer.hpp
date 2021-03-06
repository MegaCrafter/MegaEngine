#pragma once

#include <unordered_map>

#include "Scene.hpp"
#include "Shader.hpp"
#include "platform/Platform.hpp"
#include "utils/Memory.hpp"

namespace Engine {

class Renderer final {
private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ibo;
    unsigned int m_program;
    unsigned int m_batch_max_quads;

    const Scene* m_scene;

    std::unordered_map<std::string, int> m_uniform_cache;
    int get_uniform_location(const char* name);
    void prepare_render();
    void render();

    friend class Application;

public:
    Renderer(unsigned int batch_max_quads, const Scene* const scene)
        : m_batch_max_quads(batch_max_quads), m_scene(scene) {}
    ~Renderer();
    bool setup();
    void attach_shader(const Shader& shader) const;
};
}  // namespace Engine