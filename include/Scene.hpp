#pragma once

#include <iostream>

#include "ext/entt.hpp"
#include "platform/Platform.hpp"
#include "utils/Memory.hpp"

namespace Engine {

class Scene {
   private:
    entt::registry m_registry;
    class Camera* m_camera;
    Shared<const Platform> m_platform;

    friend class Entity;
    friend class Application;
    friend class Renderer;

    template <typename T, typename... Args>
    inline auto& add_component(entt::entity entity_id, Args&&... args) {
        return m_registry.emplace<T, Args...>(entity_id, std::forward<Args>(args)...);
    }

    template <typename... Component>
    inline auto& get_component(entt::entity entity_id) {
        // This had to be done here because of "auto deduction" rules
        return m_registry.get<Component...>(entity_id);
    }

    void prepare_scene() const;
    void end_scene() const;

   public:
    void set_camera(class Camera* camera);
    class Camera* camera() const;

    entt::entity new_entity();

    template <typename Component, typename... Other, typename... Exclude>
    auto entity_view(entt::exclude_t<Exclude...> exclude = {}) const {
        // This had to be done here because of "auto deduction" rules
        return m_registry.view<Component, Other..., Exclude...>(exclude);
    }

    void destroy_entity(entt::entity entity_id);

    void on_update(float delta) const;
};

}  // namespace Engine
