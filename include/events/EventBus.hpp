#pragma once

#include <vector>

#include "Event.hpp"
#include "Layer.hpp"

namespace Engine {

class EventBus {
   private:
    std::vector<const Layer*> m_layers;

   public:
    void add_layer(const Layer* layer);

    // Goes from the first added layer to the last added layer
    void submit_event(const Event& event) const;
};

}  // namespace Engine