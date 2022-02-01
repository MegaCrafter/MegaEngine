#pragma once

#include <vector>

#include "Event.hpp"

namespace Engine {

class Layer {
   public:
    // Will return true if handled
    virtual bool process_event(const Event &event) const { return false; }
};

}  // namespace Engine