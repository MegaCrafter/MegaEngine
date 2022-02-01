#if PLATFORM == GLFW
#include "platform/GlfwPlatform.hpp"

#include <GLFW/glfw3.h>

#include "events/CursorPosEvent.hpp"
#include "events/EventBus.hpp"
#include "events/WindowResizeEvent.hpp"

namespace Engine {

bool GlfwPlatform::is_key_down(int keycode) const {
    return glfwGetKey(m_window.get(), keycode) == GLFW_PRESS;
}

void GlfwPlatform::cursor_pos(double* xpos, double* ypos) const {
    glfwGetCursorPos(m_window.get(), xpos, ypos);
}

float GlfwPlatform::get_time() const {
    return glfwGetTime();
}

static const EventBus* s_eventbus;

static void on_window_resize(GLFWwindow* window, int width, int height) {
    WindowResizeEvent event(width, height);
    s_eventbus->submit_event(event);
}

static void on_cursor_pos(GLFWwindow* window, double xpos, double ypos) {
    CursorPosEvent event(xpos, ypos);
    s_eventbus->submit_event(event);
}

bool GlfwPlatform::setup_window(unsigned int width, unsigned int height, const char* name) {
    s_eventbus = m_eventbus.get();

    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = Ref<GLFWwindow, DestroyGlfwWindow>(glfwCreateWindow(width, height, name, NULL, NULL));
    if (!m_window) { return false; }

    glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowSizeCallback(m_window.get(), on_window_resize);
    glfwSetCursorPosCallback(m_window.get(), on_cursor_pos);

    glfwMakeContextCurrent(m_window.get());

    return true;
}

bool GlfwPlatform::window_should_close() {
    return glfwWindowShouldClose(m_window.get());
}

void GlfwPlatform::loop_logic() {
    glfwSwapBuffers(m_window.get());

    glfwPollEvents();
}

void GlfwPlatform::destroy() {
    glfwTerminate();
}

GlfwPlatform::~GlfwPlatform() {}

}  // namespace Engine

#endif