#pragma once

#include <visual/GLEnums.h>
#include <vector>

struct GLVertexArrayLayoutElement
{
    GLDataType data_type;
    uint32_t count;
};

using GLVertexArrayLayout = std::vector<GLVertexArrayLayoutElement>;

class GLVertexArray
{
public:

    GLVertexArray();
    ~GLVertexArray();

    auto SetLayout(GLVertexArrayLayout const& layout) const -> void;

    auto Bind() const -> void;
    auto Unbind() const -> void;

private:

    uint32_t m_ID;
};
