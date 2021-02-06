#pragma once

#include <cstdint>
#include <visual/GLEnums.h>

class GLBuffer
{
public:

    GLBuffer();
    GLBuffer(void const* data, uint32_t count, GLDataType data_type, GLBufferType buffer_type);
    ~GLBuffer();

    auto SetData(void const* data, uint32_t count, GLDataType dataType, GLBufferType data_type) -> void;

    auto GetCount() const -> uint32_t;
    auto GetDataType() const -> GLDataType;
    auto GetBufferType() const -> GLBufferType;

    auto Bind() const -> void;
    auto Unbind() const -> void;

private:

    uint32_t m_ID;
    uint32_t m_Count;
    GLDataType m_DataType;
    GLBufferType m_BufferType;
};
