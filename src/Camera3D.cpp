#include "Camera3D.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

void Camera3D::update_proj_matrix() {
    m_proj_matrix = glm::perspective(glm::radians(m_fov), m_aspect_ratio, 0.1f, 100.0f);
}

Camera3D::Camera3D(Scene* scene, float fov, float aspect_ratio)
    : Camera(scene), m_fov(fov), m_aspect_ratio(aspect_ratio) {
    update_proj_matrix();
}

void Camera3D::set_fov(float fov) {
    m_fov = fov;
    update_proj_matrix();
}

void Camera3D::set_aspect_ratio(float aspect_ratio) {
    m_aspect_ratio = aspect_ratio;
    update_proj_matrix();
}

}  // namespace Engine