#define GLEW_STATIC
#include "Application.hpp"

#include <GL/glew.h>

#include "platform/GlfwPlatform.hpp"
#include "platform/Platform.hpp"

namespace Engine {

Application::Application(unsigned int batch_max_quads, Scene* const scene, EventBus* const eventbus) {
#if PLATFORM == GLFW
    m_platform = Shared<GlfwPlatform>(new GlfwPlatform(eventbus));
#endif

    scene->m_platform = m_platform;
    m_renderer = Ref<Renderer>(new Renderer(batch_max_quads, scene));
}

bool Application::start_window(unsigned int width, unsigned int height, const char* name) {
    bool window_success = m_platform->setup_window(width, height, name);
    if (!window_success) return false;

    if (glewInit() != GLEW_OK) return false;

    return m_renderer->setup();
}

void Application::loop() {
    m_renderer->prepare_render();

    while (!m_platform->window_should_close()) {
        m_renderer->render();

        m_platform->loop_logic();
    }
}

void Application::destroy() {
    m_platform->destroy();
}


void Application::attach_shader(const Shader& shader) {
    m_renderer->attach_shader(shader);
}

}  // namespace Engine