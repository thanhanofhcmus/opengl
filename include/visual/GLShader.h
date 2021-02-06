#pragma once

#include <visual/GLEnums.h>
#include <glm/glm.hpp>

#include <string>

class GLShader
{
public:

    GLShader();
    GLShader(std::string const& vertex_shader_filename, std::string const& fragment_shader_filename);
    ~GLShader();

    auto LoadFromFile(std::string const& vertex_shader_filename, std::string const& fragment_shader_filename) -> void;
    auto LoadFromMemory(std::string const& vertex_shader_souce, std::string const& fragment_shader_source) -> void;

    auto Bind() const -> void;
    auto Unbind() const -> void;

    auto SendUniform1f(std::string const& name, float value) const -> void;
    auto SendUniform1i(std::string const& name, int value) const -> void;
    auto SendUniform4f(std::string const& name, glm::vec4 const& vec) const -> void;
    auto SendUniformMatrix4f(std::string const& name, glm::mat4 const& mat) const -> void;

private:

    auto ReadFullFile(std::string const& file_name) -> std::string;

    auto CompileShader(const char* source, GLShaderType type) -> int;

    auto LinkShaders(uint32_t vertex_ID, uint32_t fragment_ID) -> void;

    auto CheckCompileError(uint32_t ID, GLShaderType type) -> void;

    auto GetUniformLocation(std::string const& name) const -> int;

private:

    uint32_t m_ID;
};
