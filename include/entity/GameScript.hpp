#pragma once

#include "entity/Entity.hpp"
#include "platform/Platform.hpp"
#include "utils/Memory.hpp"

namespace Engine {

class GameScript {
   private:
    friend class Scene;
    friend class ScriptComponent;

    Shared<const Platform> m_platform;

   protected:
    Entity* m_entity;

    virtual void on_create() {}
    virtual void on_update(float delta) {}
    virtual void on_destroy() {}

    bool is_key_down(int keycode) const {
        return m_platform->is_key_down(keycode);
    }

    void cursor_pos(double* xpos, double* ypos) const {
        m_platform->cursor_pos(xpos, ypos);
    }

   public:
    virtual ~GameScript() {}
};
}  // namespace Engine