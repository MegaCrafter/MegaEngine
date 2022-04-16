#pragma once

#include "events/EventBus.hpp"
#include "utils/Memory.hpp"

namespace Engine {

class Platform {
protected:
    const EventBus* m_eventbus;

    virtual bool is_key_down(int keycode) const {
        return false;
    }

    virtual void cursor_pos(double* xpos, double* ypos) const {}

    virtual float get_time() const {
        return 0;
    }

    friend class GameScript;

public:
    explicit Platform(const EventBus* const eventbus): m_eventbus(eventbus) {}
    virtual bool setup_window(unsigned int width, unsigned int height, const char* name) {
        return false;
    }
    virtual bool window_should_close() {
        return true;
    }
    virtual void loop_logic() {}
    virtual void destroy() {}
};

}  // namespace Engine