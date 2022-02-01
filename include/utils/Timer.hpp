#pragma once

#include "display/Display.hpp"

namespace Engine {

class Timer {
   protected:
    const Display* const m_display;

   public:
    Timer(const Display* const display) : m_display(display) {}

    virtual float get_time() {
        return 0;
    }
};

}  // namespace Engine