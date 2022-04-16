#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

struct TransformComponent {
private:
    glm::vec3 position = { 0, 0, 0 };
    glm::vec3 rotation = { 0, 0, 0 };
    glm::vec3 scaling = { 1, 1, 1 };

    glm::vec3 upvec = { 0, 1, 0 };
    glm::vec3 rightvec = { 1, 0, 0 };

    void update_rotX(float angle) {
        upvec = glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 1, 0, 0 }) * glm::vec4(upvec, 1.0f);
        rightvec = glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 1, 0, 0 }) * glm::vec4(rightvec, 1.0f);
    }
    void update_rotY(float angle) {
        upvec = glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 0, 1, 0 }) * glm::vec4(upvec, 1.0f);
        rightvec = glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 0, 1, 0 }) * glm::vec4(rightvec, 1.0f);
    }
    void update_rotZ(float angle) {
        upvec = glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 0, 0, 1 }) * glm::vec4(upvec, 1.0f);
        rightvec = glm::rotate(glm::mat4(1.0f), glm::radians(angle), { 0, 0, 1 }) * glm::vec4(rightvec, 1.0f);
    }
    void update_rot_custom(float angle, glm::vec3 vec) {
        upvec = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vec) * glm::vec4(upvec, 1.0f);
        rightvec = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vec) * glm::vec4(rightvec, 1.0f);
    }

public:
    void set_position(float x, float y, float z) {
        position = { x, y, z };
    }
    void set_rotationX(float angle) {
        rotation = { angle, rotation.y, rotation.z };
        update_rotX(angle);
    }
    void set_rotationY(float angle) {
        rotation = { rotation.x, angle, rotation.z };
        update_rotY(angle);
    }
    void set_rotationZ(float angle) {
        rotation = { rotation.x, rotation.y, angle };
        update_rotZ(angle);
    }
    void set_rotation(float x, float y, float z) {
        set_rotationX(x);
        set_rotationY(y);
        set_rotationZ(z);
    }
    void set_scale(float x, float y, float z) {
        scaling = { x, y, z };
        // TODO: up direction might change with scale
    }

    void translate(float x, float y, float z) {
        position += glm::vec3(x, y, z);
    }

    void rotateX(float angle) {
        rotation += glm::vec3(angle, 0, 0);
        update_rotX(angle);
    }
    void rotateY(float angle) {
        rotation += glm::vec3(0, angle, 0);
        update_rotY(angle);
    }
    void rotateZ(float angle) {
        rotation += glm::vec3(0, 0, angle);
        update_rotZ(angle);
    }
    void rotate_custom(float angle, glm::vec3 vec) {
        rotation += glm::vec3(vec.x * angle, vec.y * angle, vec.z * angle);
        update_rot_custom(angle, vec);
    }

    inline glm::vec3 up() const {
        return upvec;
    }
    inline glm::vec3 right() const {
        return rightvec;
    }
    inline glm::vec3 front() const {
        return glm::cross(upvec, rightvec);
    }
    inline glm::vec3 get_position() {
        return position;
    }
    inline glm::vec3 get_rotation() {
        return rotation;
    }

    glm::mat4 model_matrix() const {
        glm::mat4 transmat = glm::translate(glm::mat4(1.0f), position);

        glm::mat4 scalemat = glm::scale(glm::mat4(1.0f), scaling);

        glm::mat4 rotmat = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), { 1, 0, 0 }) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), { 0, 1, 0 }) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), { 0, 0, 1 });

        return transmat * scalemat * rotmat;
    }
};
}  // namespace Engine