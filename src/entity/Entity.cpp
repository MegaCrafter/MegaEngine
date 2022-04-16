#include "entity/Entity.hpp"

namespace Engine {

Entity::Entity(Scene* scene): m_scene(scene) {
    m_entity_id = m_scene->new_entity();

    add_component<TransformComponent>();
}

Entity::~Entity() {
    m_scene->destroy_entity(m_entity_id);
}

}  // namespace Engine