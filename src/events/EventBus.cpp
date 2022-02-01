#include "events/EventBus.hpp"

namespace Engine {

void EventBus::add_layer(const Layer* layer) { m_layers.push_back(layer); }

void EventBus::submit_event(const Event& event) const {
    for (const Layer* layer : m_layers) {
        bool handled = layer->process_event(event);
        if (handled) break;
    }
}

}  // namespace Engine