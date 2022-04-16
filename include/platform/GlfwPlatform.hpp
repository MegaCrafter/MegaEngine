#pragma once

#if PLATFORM == GLFW

#include <GLFW/glfw3.h>

#include "events/EventBus.hpp"
#include "platform/Platform.hpp"
#include "utils/Memory.hpp"

namespace Engine {

class GlfwPlatform final : public Platform {
private:
    GLFWwindow* m_window;

protected:
    virtual bool is_key_down(int keycode) const override;
    virtual void cursor_pos(double* xpos, double* ypos) const override;

    virtual float get_time() const override;

public:
    explicit GlfwPlatform(const EventBus* const eventbus): Platform(eventbus) {}
    ~GlfwPlatform();
    virtual bool setup_window(unsigned int width, unsigned int height, const char* name) override;
    virtual bool window_should_close() override;
    virtual void loop_logic() override;
    virtual void destroy() override;
};

}  // namespace Engine

#endif