#pragma once

#include "Scene.hpp"
#include "entity/TransformComponent.hpp"
#include "ext/entt.hpp"
#include "utils/Memory.hpp"

namespace Engine {

class Entity {
private:
    entt::entity m_entity_id;
    Scene* m_scene;

public:
    explicit Entity(Scene* scene);
    ~Entity();

    template <typename T, typename... Args>
    inline T& add_component(Args&&... args) {
        return m_scene->add_component<T, Args...>(m_entity_id, std::forward<Args>(args)...);
    }

    template <typename... Component>
    inline auto& get_component() const {
        // This had to be done here because of "auto deduction" rules
        return m_scene->get_component<Component...>(m_entity_id);
    }

    inline TransformComponent& transform() const {
        return get_component<TransformComponent>();
    }
};
}  // namespace Engine