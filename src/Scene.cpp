#include "Scene.hpp"

#include "Camera.hpp"
#include "entity/ScriptComponent.hpp"

namespace Engine {

void Scene::prepare_scene() const {
    auto view = entity_view<ScriptComponent>();

    for (auto [entity, script_comp] : view.each()) {
        ScriptComponent& mut_script_comp = const_cast<ScriptComponent&>(script_comp);
        mut_script_comp.m_game_script = Ref<GameScript>(script_comp.init_script());

        mut_script_comp.m_game_script->m_entity = script_comp.m_entity;
        mut_script_comp.m_game_script->m_platform = m_platform;

        script_comp.m_game_script->on_create();
    }
}

void Scene::end_scene() const {
    auto view = entity_view<ScriptComponent>();

    for (auto [entity, script_comp] : view.each()) { script_comp.m_game_script->on_destroy(); }
}

void Scene::set_camera(Camera* camera) {
    m_camera = camera;
}

Camera* Scene::camera() const {
    return m_camera;
}

entt::entity Scene::new_entity() {
    return m_registry.create();
}

void Scene::destroy_entity(entt::entity entity_id) {
    m_registry.destroy(entity_id);
}

void Scene::on_update(float delta) const {
    auto view = entity_view<ScriptComponent>();

    for (auto [entity, script_comp] : view.each()) { script_comp.m_game_script->on_update(delta); }
}

}  // namespace Engine