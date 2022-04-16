#include <iostream>

#include "Application.hpp"
#include "Camera.hpp"
#include "Camera3D.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "entity/Entity.hpp"
#include "entity/MeshComponent.hpp"
#include "entity/ScriptComponent.hpp"
#include "entity/TransformComponent.hpp"
#include "entity/Vertex.hpp"
#include "events/EventBus.hpp"
#include "events/Layer.hpp"
#include "events/ViewportLayer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "helpers/FirstPersonWalkingCamera.hpp"

int main(int argc, char** argv) {
    {
        Engine::Scene scene;

        Engine::EventBus eventbus;
        Engine::ViewportLayer viewportLayer;
        eventbus.add_layer(&viewportLayer);

        Engine::Application app(10000, &scene, &eventbus);
        bool app_success = app.start_window(1280, 720, "OpenGL Engine");
        if (!app_success) {
            app.destroy();
            return -1;
        }

        Engine::Camera3D camera(&scene, 45.0f, 16.0f / 9.0f);

        camera.transform().set_position(1, 0, 0);

        camera.add_component<Engine::ScriptComponent>(&camera).bind<Engine::FirstPersonWalkingCamera>();

        Engine::Vertex vertices[] = {
            {1.0f, 1.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},
            {1.0f, -1.0f, 1.0f},

            {1.0f, 1.0f, -1.0f},
            {-1.0f, 1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f},
            {1.0f, -1.0f, -1.0f},
        };

        unsigned int indices[] = {
            0, 1, 2, 0, 2, 3,
            0, 3, 4, 3, 4, 7,
            0, 1, 4, 1, 4, 5,
            4, 5, 6, 4, 6, 7,
            1, 5, 6, 1, 2, 6,
            2, 3, 6, 3, 6, 7,
        };

        Engine::Entity entity(&scene);
        entity.add_component<Engine::MeshComponent>(vertices, indices, 8, 6 * 6);

        entity.transform().set_position(-2, 0, -7);

        Engine::Entity entity2(&scene);
        entity2.add_component<Engine::MeshComponent>(vertices, indices, 8, 6 * 6);

        entity2.transform().set_rotation(0, 0, -45);
        glm::vec3 up = entity2.transform().up();

        entity2.transform().set_position(2 * up.x + 3, 2 * up.y, 2 * up.z - 8);

        // TODO: Add debug stuff
        // GLint success;
        // GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        // glShaderSource(vs, 1, &vertex_shader, NULL);
        // glCompileShader(vs);
        // glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        // if (!success) {
        //     char infoLog[512];
        //     glGetShaderInfoLog(vs, 512, NULL, infoLog);
        //     std::cout << infoLog << std::endl;
        //     return 1;
        // }

        // GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        // glShaderSource(fs, 1, &fragment_shader, NULL);
        // glCompileShader(fs);
        // glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        // if (!success) {
        //     char infoLog[512];
        //     glGetShaderInfoLog(vs, 512, NULL, infoLog);
        //     std::cout << infoLog << std::endl;
        //     return 1;
        // }

        // TODO: Abstract program
        Engine::Shader vert_shader(Engine::ShaderType::VERTEX_SHADER, "assets/shaders/basic_vertex.glsl");

        Engine::Shader frag_shader(Engine::ShaderType::FRAGMENT_SHADER, "assets/shaders/basic_fragment.glsl");

        app.attach_shader(vert_shader);
        app.attach_shader(frag_shader);

        app.loop();
    }
    return 0;
}
