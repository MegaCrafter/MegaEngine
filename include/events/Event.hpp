#pragma once

namespace Engine {

enum EventType {
    WINDOW_RESIZE,
    CURSOR_POS,
};

class Event {
   protected:
    EventType m_type;

   public:
    Event(EventType type) : m_type(type) {}

    inline EventType type() const { return m_type; }
};

}  // namespace Engine