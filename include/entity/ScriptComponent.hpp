#pragma once

#include <concepts>

#include "entity/Entity.hpp"
#include "entity/GameScript.hpp"
#include "platform/Platform.hpp"
#include "utils/Memory.hpp"

namespace Engine {

struct ScriptComponent {
    Entity* m_entity;
    Ref<GameScript> m_game_script;

    GameScript* (*init_script)();

    template <typename Script>
    requires std::derived_from<Script, GameScript>
    void bind() {
        init_script = []() { return static_cast<GameScript*>(new Script()); };
    }
};
}  // namespace Engine