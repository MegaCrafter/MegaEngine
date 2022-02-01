#pragma once

#include "Renderer.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "events/EventBus.hpp"
#include "platform/Platform.hpp"
#include "utils/Memory.hpp"

namespace Engine {

class Application {
   private:
    Shared<Platform> m_platform;
    Ref<Renderer> m_renderer;

   public:
    Application(unsigned int batch_max_quads, Scene* const scene, EventBus* const eventbus);

    bool start_window(unsigned int width, unsigned int height, const char* name);
    void loop();
    void destroy();

    void attach_shader(const Shader& shader);
};

}  // namespace Engine