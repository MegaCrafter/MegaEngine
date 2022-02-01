#include "events/ViewportLayer.hpp"

#include <GL/glew.h>

#include "events/WindowResizeEvent.hpp"

namespace Engine {

bool ViewportLayer::process_event(const Event& event) const {
    if (event.type() == EventType::WINDOW_RESIZE) {
        const WindowResizeEvent resize_event =
            static_cast<const WindowResizeEvent&>(event);

        glViewport(0, 0, resize_event.width(), resize_event.height());
    }

    return false;
}

}  // namespace Engine