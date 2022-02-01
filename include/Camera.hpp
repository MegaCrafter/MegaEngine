#pragma once

#include "entity/Entity.hpp"
#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
#include "entity/TransformComponent.hpp"

namespace Engine {

class Camera : public Entity {
   protected:
    glm::mat4 m_proj_matrix;

   public:
    Camera(Scene* scene) : Entity(scene) {
        scene->set_camera(this);
    };

    inline glm::mat4 projection_matrix() const {
        return m_proj_matrix;
    }

    glm::mat4 camera_matrix() const {
        // // TODO: Maybe faster somehow?
        // TransformComponent& transform = get_component<TransformComponent>();
        // return glm::inverse(transform.model_matrix());
        TransformComponent& transform = get_component<TransformComponent>();
        return glm::lookAt(transform.get_position(), transform.get_position() + transform.front(),
                           transform.up());
    }
};

}  // namespace Engine