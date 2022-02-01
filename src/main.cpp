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

// float defTB = 0.9f;
// glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), 16.0f / 9, 0.1f, 100.0f);
// // glm::ortho(-defTB * 16 / 9, defTB * 16 / 9, -defTB, defTB, 1.0f, -1.0f);

// glm::vec3 camera_pos = {0, 0, 0};
// glm::vec3 camera_up = {0, 1, 0};
// glm::vec3 camera_front = {0, 0, -1};
// float camera_yaw = -90;
// float camera_pitch = 0;

// void on_window_resize(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);

//     float aspect_ratio = (float)width / height;
//     projection_matrix = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f);
//     // projection_matrix = glm::ortho(-defTB * aspect_ratio, defTB *
//     // aspect_ratio,
//     //                                -defTB, defTB, 1.0f, -1.0f);
// }

// void process_input(GLFWwindow* window) {
//     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//         camera_pos += 0.1f * glm::vec3{camera_front.x, 0, camera_front.z};
//     }
//     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//         camera_pos += 0.1f * glm::normalize(glm::cross(camera_front, camera_up));
//     }
//     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//         camera_pos += 0.1f * -glm::vec3{camera_front.x, 0, camera_front.z};
//     }
//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//         camera_pos += 0.1f * -glm::normalize(glm::cross(camera_front, camera_up));
//     }
// }

// float lastX = 1280.0 / 2, lastY = 720.0 / 2;
// bool firstCursor = true;
// void on_cursor(GLFWwindow* window, double xpos, double ypos) {
//     if (firstCursor) {
//         lastX = xpos;
//         lastY = ypos;
//         firstCursor = false;
//         return;
//     }

//     float xoff = xpos - lastX;
//     float yoff = lastY - ypos;
//     lastX = xpos;
//     lastY = ypos;

//     constexpr float sensitivity = 0.2f;
//     xoff *= sensitivity;
//     yoff *= sensitivity;

//     camera_yaw += xoff;
//     camera_pitch = glm::clamp(camera_pitch + yoff, -89.0f, 89.0f);

//     glm::vec3 dir;
//     dir.x = cos(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
//     dir.y = sin(glm::radians(camera_pitch));
//     dir.z = sin(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));

//     camera_front = dir;
// }

int main(int argc, char** argv) {
    // GLFWwindow* window;

    // if (!glfwInit()) return -1;

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    // if (!window) {
    //     glfwTerminate();
    //     return -1;
    // }

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glfwSetWindowSizeCallback(window, on_window_resize);
    // glfwSetCursorPosCallback(window, on_cursor);

    // glfwMakeContextCurrent(window);

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

    camera.add_component<Engine::ScriptComponent>(&camera);
    Engine::ScriptComponent& script_comp = camera.get_component<Engine::ScriptComponent>();
    script_comp.bind<Engine::FirstPersonWalkingCamera>();

    // clang-format off
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
    // clang-format on

    // clang-format off
    unsigned int indices[] = {
        0, 1, 2, 0, 2, 3,
        0, 3, 4, 3, 4, 7,
        0, 1, 4, 1, 4, 5,
        4, 5, 6, 4, 6, 7,
        1, 5, 6, 1, 2, 6,
        2, 3, 6, 3, 6, 7,
    };
    // clang-format on

    // entt::entity entity = registry.create();
    // registry.emplace<Engine::MeshComponent>(entity, vertices, indices, 8,
    //                                         6 * 6);
    // registry.emplace<Engine::TransformComponent>(entity);

    // registry.get<Engine::TransformComponent>(entity).set_position(-2, 0, -7);

    Engine::Entity entity(&scene);
    entity.add_component<Engine::MeshComponent>(vertices, indices, 8, 6 * 6);

    entity.transform().set_position(-2, 0, -7);

    // entt::entity entity2 = registry.create();
    // registry.emplace<Engine::MeshComponent>(entity2, vertices2, indices2, 8,
    //                                         6 * 6);
    // registry.emplace<Engine::TransformComponent>(entity2);

    // registry.get<Engine::TransformComponent>(entity2).set_rotation(0, 0,
    // -45); Engine::TransformComponent& transform =
    //     registry.get<Engine::TransformComponent>(entity2);
    // glm::vec3 up = transform.up();

    // transform.set_position(2 * up.x + 3, 2 * up.y, 2 * up.z - 8);

    Engine::Entity entity2(&scene);
    entity2.add_component<Engine::MeshComponent>(vertices, indices, 8, 6 * 6);

    entity2.transform().set_rotation(0, 0, -45);
    glm::vec3 up = entity2.transform().up();

    entity2.transform().set_position(2 * up.x + 3, 2 * up.y, 2 * up.z - 8);

    // GLuint vao;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    // GLuint vbo;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
    // GL_STATIC_DRAW);

    // GLuint ibo;
    // glGenBuffers(1, &ibo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
    //              GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
    // 0); glEnableVertexAttribArray(0);

    // glBindVertexArray(0);

    // const char* vertex_shader =
    //     "#version 330 core\n"
    //     "layout(location = 0) in vec4 pos;\n"
    //     "uniform mat4 proj;\n"
    //     "uniform mat4 cam;"
    //     "void main() {\n"
    //     "   gl_Position = proj * cam * pos;\n"
    //     "}";

    // const char* fragment_shader =
    //     "#version 330 core\n"
    //     "out vec4 FragColor;\n"
    //     "void main() {\n"
    //     " FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
    //     "}";

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

    Engine::Shader vert_shader(Engine::ShaderType::VERTEX_SHADER, "assets/shaders/basic_vertex.glsl");

    Engine::Shader frag_shader(Engine::ShaderType::FRAGMENT_SHADER, "assets/shaders/basic_fragment.glsl");

    // GLuint program = glCreateProgram();
    // glAttachShader(program, vert_shader.shader_id());
    // glAttachShader(program, frag_shader.shader_id());
    // glLinkProgram(program);

    // glGetProgramiv(program, GL_LINK_STATUS, &success);
    // if (!success) {
    //     char infoLog[512];
    //     glGetProgramInfoLog(program, 512, NULL, infoLog);
    //     std::cout << infoLog << std::endl;
    //     return 1;
    // }

    // glDeleteShader(vs);
    // glDeleteShader(fs);

    // renderer.attach_shader(vert_shader);
    // renderer.attach_shader(frag_shader);

    app.attach_shader(vert_shader);
    app.attach_shader(frag_shader);

    // display.loop();
    app.loop();

    // camera_front = glm::normalize(glm::vec3{cos(glm::radians(camera_yaw)), 0,
    //                                         sin(glm::radians(camera_yaw))});
    // while (!glfwWindowShouldClose(window)) {
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //     glUseProgram(program);
    //     glBindVertexArray(vao);

    //     glEnable(GL_DEPTH_TEST);

    //     GLint loc = glGetUniformLocation(program, "proj");
    //     glUniformMatrix4fv(loc, 1, GL_FALSE, &projection_matrix[0][0]);
    //     loc = glGetUniformLocation(program, "cam");
    //     glm::mat4 camera_matrix =
    //         glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
    //     glUniformMatrix4fv(loc, 1, GL_FALSE, &camera_matrix[0][0]);
    //     glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);

    //     glfwSwapBuffers(window);

    //     glfwPollEvents();
    //     process_input(window);
    // }

    // display.destroy();
    app.destroy();
    return 0;
}
