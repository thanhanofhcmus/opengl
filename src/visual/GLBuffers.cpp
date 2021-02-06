#include <visual/GLBuffers.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLBuffer::GLBuffer()
    : m_Count{0}, m_DataType{GLDataType::Invalid}, m_BufferType{GLBufferType::Invalid}
    { glGenBuffers(1, &m_ID); }

GLBuffer::GLBuffer(void const* data, uint32_t count, GLDataType data_type, GLBufferType buffer_type)
    : m_Count(count), m_DataType{data_type}, m_BufferType{buffer_type}
{
    glGenBuffers(1, &m_ID);
    SetData(data, count, data_type, buffer_type);
}

GLBuffer::~GLBuffer() { glDeleteBuffers(1, &m_ID); }

auto GLBuffer::SetData(void const* data, uint32_t count, GLDataType data_type, GLBufferType buffer_type) -> void
{
    Bind();
    glBufferData(static_cast<GLenum>(buffer_type), count * GLGetDataSize(data_type), data, GL_STATIC_DRAW);

    m_Count = count;
    m_DataType = data_type;
    m_BufferType = buffer_type;
}

auto GLBuffer::GetCount() const -> uint32_t { return m_Count; }

auto GLBuffer::GetDataType() const -> GLDataType { return m_DataType; }

auto GLBuffer::GetBufferType() const -> GLBufferType { return m_BufferType; }

auto GLBuffer::Bind() const -> void { glBindBuffer(static_cast<GLenum>(m_BufferType), m_ID); }

auto GLBuffer::Unbind() const -> void { glBindBuffer(static_cast<GLenum>(m_BufferType), 0); }
