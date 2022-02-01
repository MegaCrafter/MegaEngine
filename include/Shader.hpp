#pragma once

namespace Engine {

enum ShaderType {
    VERTEX_SHADER,
    FRAGMENT_SHADER,
};

class Shader {
   private:
    unsigned int m_shader_id;
    ShaderType m_type;

   public:
    Shader(ShaderType type, const char* filename);
    ~Shader();
    inline unsigned int shader_id() const { return m_shader_id; }
};

}  // namespace Engine