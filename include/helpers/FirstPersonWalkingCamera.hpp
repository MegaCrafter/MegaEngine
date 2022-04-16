#pragma once

#include "Camera.hpp"
#include "entity/GameScript.hpp"
#include "entity/TransformComponent.hpp"
#include "glm/glm.hpp"
#include "input/Keys.hpp"

namespace Engine {

class FirstPersonWalkingCamera : public GameScript {
private:
    Camera* m_camera;
    double m_lastx = 0;
    double m_lasty = 0;
    bool first = true;

protected:
    virtual void on_create() {
        m_camera = static_cast<Camera*>(m_entity);
    }
    virtual void on_update(float delta) override {
        TransformComponent& transform = m_camera->get_component<TransformComponent>();
        glm::vec3 front = transform.front();
        glm::vec3 right = transform.right();
        if (is_key_down(ENGINE_KEY_D)) {
            transform.translate(right.x * 0.1f, right.y * 0.1f, right.z * 0.1f);
        }
        if (is_key_down(ENGINE_KEY_W)) { transform.translate(front.x * 0.1f, 0, front.z * 0.1f); }
        if (is_key_down(ENGINE_KEY_A)) {
            transform.translate(right.x * -0.1f, right.y * -0.1f, right.z * -0.1f);
        }
        if (is_key_down(ENGINE_KEY_S)) { transform.translate(front.x * -0.1f, 0, front.z * -0.1f); }

        double xpos;
        double ypos;
        cursor_pos(&xpos, &ypos);

        double xoff = xpos - m_lastx;
        double yoff = m_lasty - ypos;
        m_lastx = xpos;
        m_lasty = ypos;

        if (first) {
            first = false;
            return;
        }

        transform.rotate_custom(yoff * 0.2f, right);
        transform.rotateY(-xoff * 0.2f);
    }
};

}  // namespace Engine