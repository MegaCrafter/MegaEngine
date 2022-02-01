#pragma once

#include "Event.hpp"

namespace Engine {

class WindowResizeEvent : public Event {
   private:
    int m_width;
    int m_height;

   public:
    WindowResizeEvent(int width, int height)
        : Event(EventType::WINDOW_RESIZE), m_width(width), m_height(height) {}

    inline int width() const { return m_width; }
    inline int height() const { return m_height; }
};

}  // namespace Engine