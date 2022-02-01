#include "Renderer.hpp"

#include <GL/glew.h>
#include <GL/glu.h>

#include <utility>

#include "Camera.hpp"
#include "entity/MeshComponent.hpp"
#include "entity/TransformComponent.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

int Renderer::get_uniform_location(const char* name) {
    if (m_uniform_cache.contains(name)) { return m_uniform_cache[name]; }

    int loc = glGetUniformLocation(m_program, name);
    m_uniform_cache[name] = loc;
    return loc;
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

bool Renderer::setup() {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_batch_max_quads * 4, NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_batch_max_quads * 6, NULL, GL_DYNAMIC_DRAW);

    glBindVertexArray(0);

    m_program = glCreateProgram();

    return true;
}

void Renderer::attach_shader(const Shader& shader) const {
    glAttachShader(m_program, shader.shader_id());
}

void Renderer::prepare_render() {
    m_scene->prepare_scene();
}

void Renderer::render() {
    m_scene->on_update(1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    glBindVertexArray(m_vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex::pos), offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glLinkProgram(m_program);
    glUseProgram(m_program);

    glm::mat4 projection_matrix = m_scene->camera()->projection_matrix();
    int loc = get_uniform_location("proj");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &projection_matrix[0][0]);

    glm::mat4 camera_matrix = m_scene->camera()->camera_matrix();
    loc = get_uniform_location("cam");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &camera_matrix[0][0]);

    unsigned int index_count = 0;
    unsigned int vertex_count = 0;

    // TODO: Move these allocations out of render()
    Vertex* vertices = new Vertex[m_batch_max_quads * 4];
    unsigned int* indices = new unsigned int[m_batch_max_quads * 6];

    auto view = m_scene->entity_view<MeshComponent, TransformComponent>();
    for (auto [entity, mesh, transform] : view.each()) {
        // TODO: Batch rendering w/ textures
        if (mesh.index_count + index_count > m_batch_max_quads * 6) {
            glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);

            index_count = 0;
            vertex_count = 0;
        }

        for (int i = 0; i < mesh.vertex_count; i++) {
            vertices[i] = mesh.vertices[i].transformed(transform.model_matrix());
        }

        glBufferSubData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), mesh.vertex_count * sizeof(Vertex),
                        vertices);

        for (int i = 0; i < mesh.index_count; i++) { indices[i] = mesh.indices[i] + vertex_count; }

        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int),
                        mesh.index_count * sizeof(unsigned int), indices);

        index_count += mesh.index_count;
        vertex_count += mesh.vertex_count;
    }

    delete[] vertices;
    delete[] indices;

    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
}

}  // namespace Engine
