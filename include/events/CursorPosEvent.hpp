#pragma once

#include "Event.hpp"

namespace Engine {

class CursorPosEvent : public Event {
   private:
    double m_xpos;
    double m_ypos;

   public:
    CursorPosEvent(double xpos, double ypos)
        : Event(EventType::CURSOR_POS), m_xpos(xpos), m_ypos(ypos) {}

    inline double xpos() { return m_xpos; }
    inline double ypos() { return m_ypos; }
};

}  // namespace Engine