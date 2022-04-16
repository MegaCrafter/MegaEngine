#include "Shader.hpp"

#include <GL/glew.h>

#include "utils/Utils.hpp"

namespace Engine {

Shader::Shader(ShaderType type, const char* filename): m_type(type) {
    std::string contents = read_file(filename);

    GLenum shader_type;
    switch (type) {
        case VERTEX_SHADER:
            shader_type = GL_VERTEX_SHADER;
            break;
        case FRAGMENT_SHADER:
            shader_type = GL_FRAGMENT_SHADER;
            break;
    }

    m_shader_id = glCreateShader(shader_type);

    const char* contents_c = contents.c_str();
    glShaderSource(m_shader_id, 1, &contents_c, NULL);

    glCompileShader(m_shader_id);

    // GLint success;
    // glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //     char infoLog[512];
    //     glGetShaderInfoLog(vs, 512, NULL, infoLog);
    //     std::cout << infoLog << std::endl;
    //     return 1;
    // }
}

Shader::~Shader() {
    glDeleteShader(m_shader_id);
}

}  // namespace Engine