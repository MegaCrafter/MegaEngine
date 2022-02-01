#pragma once

#include "Camera.hpp"

namespace Engine {

class Camera3D : public Camera {
   private:
    float m_fov;
    float m_aspect_ratio;

    void update_proj_matrix();

   public:
    Camera3D(Scene* scene, float fov, float aspect_ratio);

    inline float fov() {
        return m_fov;
    }

    inline float aspect_ratio() {
        return m_aspect_ratio;
    }

    void set_fov(float fov);
    void set_aspect_ratio(float aspect_ratio);
};
}  // namespace Engine