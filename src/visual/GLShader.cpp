#include <visual/GLShader.h>
#include <Log.h>
#include <glm/ext.hpp>

#include <fstream>
#include <glad/glad.h>

GLShader::GLShader() { m_ID = glCreateProgram(); }

GLShader::GLShader(std::string const& vertex_filename, std::string const& fragment_filename)
{
    m_ID = glCreateProgram();
    LoadFromFile(vertex_filename, fragment_filename);
}

GLShader::~GLShader() { glDeleteProgram(m_ID); }

auto GLShader::LoadFromFile(std::string const& vertex_filename, std::string const& fragment_filename) -> void
{
    std::string vertex_source = ReadFullFile(vertex_filename);
    std::string fragment_source = ReadFullFile(fragment_filename);

    uint32_t vertex_ID = CompileShader(vertex_source.c_str(), GLShaderType::Vertex);
    uint32_t fragment_ID = CompileShader(fragment_source.c_str(), GLShaderType::Fragment);

    LinkShaders(vertex_ID, fragment_ID);

    glDeleteShader(vertex_ID);
    glDeleteShader(fragment_ID);
}

auto GLShader::LoadFromMemory(std::string const& vertex_source, std::string const& fragment_source) -> void
{
    uint32_t vertex_ID = CompileShader(vertex_source.c_str(), GLShaderType::Vertex);
    uint32_t fragment_ID = CompileShader(fragment_source.c_str(), GLShaderType::Fragment);

    LinkShaders(vertex_ID, fragment_ID);

    glDeleteShader(vertex_ID);
    glDeleteShader(fragment_ID);
}

auto GLShader::Bind() const -> void { glUseProgram(m_ID); }

auto GLShader::Unbind() const -> void { glUseProgram(0); }

auto GLShader::ReadFullFile(std::string const& filename) -> std::string
{
    std::ifstream file(filename);

    if (!file)
    {
        LOG_ERROR("File \"{}\" not found", filename);
        std::terminate();
    }

    file.seekg(0, std::ios::end);
    const size_t size = file.tellg();
    std::string content;
    content.reserve(size);
    file.seekg(0, std::ios::beg);
    file.read(&content[0], size);

    return content;
}

auto GLShader::CompileShader(char const* source, GLShaderType type) -> int
{
    uint32_t ID = glCreateShader(static_cast<GLenum>(type));
    glShaderSource(ID, 1, &source, nullptr);
    glCompileShader(ID);
    CheckCompileError(ID, type);

    return ID;
}

auto GLShader::LinkShaders(uint32_t vertex_ID, uint32_t fragment_ID) -> void
{
    glAttachShader(m_ID, vertex_ID);
    glAttachShader(m_ID, fragment_ID);
    glLinkProgram(m_ID);
    CheckCompileError(m_ID, GLShaderType::Invalid);
}

auto GLShader::CheckCompileError(uint32_t ID, GLShaderType type) -> void
{
    GLint success;
    GLchar infolog[1024];
    if (type == GLShaderType::Invalid)
    {
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, sizeof(infolog), nullptr, infolog);
            LOG_ERROR("Linker: {}", infolog);
        }
    }
    else
    {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(ID, sizeof(infolog), nullptr, infolog);
            LOG_ERROR("{}: {}",
                      ((type == GLShaderType::Vertex) ? "Vertex" : "Fragment"), infolog);
        }
    }
}

auto GLShader::GetUniformLocation(std::string const& name) const -> int
{
    int location = glGetUniformLocation(m_ID, name.c_str());

    if (location == -1)
        LOG_WARN("GLShader::GetUniformLocation: Invalid uniform name \"{}\"", name);

    return location;
}

auto GLShader::SendUniform1f(std::string const& name, float value) const -> void
{ glUniform1f(GetUniformLocation(name), value); }

auto GLShader::SendUniform1i(std::string const& name, int value) const -> void
{ glUniform1i(GetUniformLocation(name), value); }

auto GLShader::SendUniform4f(std::string const& name, glm::vec4 const& vec) const -> void
{ glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w); }

auto GLShader::SendUniformMatrix4f(std::string const& name, glm::mat4 const& mat) const -> void
{ glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)); }
