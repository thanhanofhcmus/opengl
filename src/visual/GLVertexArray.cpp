#include <visual/GLVertexArray.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Log.h>

#include <numeric>

GLVertexArray::GLVertexArray()
{
    glGenVertexArrays(1, &m_ID);
}

GLVertexArray::~GLVertexArray() { glDeleteVertexArrays(1, &m_ID); }

auto GLVertexArray::SetLayout(GLVertexArrayLayout const& layout) const -> void
{
    uint32_t index = 0;
    // Must use pointer diff type or it'll fuck up
    std::ptrdiff_t offset = 0;
    uint32_t stride = std::accumulate(layout.cbegin(), layout.cend(), 0,
                  [](int sum, auto const& elem) { return sum + elem.count * GLGetDataSize(elem.data_type); });

    for (auto const& element : layout)
    {
        // Maybe considered not alway using GL_FALSE
        glVertexAttribPointer(index, element.count, static_cast<GLenum>(element.data_type),
                              GL_FALSE, stride, (void const*)(offset));
        glEnableVertexAttribArray(index);

        index++;
        offset += element.count * GLGetDataSize(element.data_type);
    }
}

auto GLVertexArray::Bind() const -> void { glBindVertexArray(m_ID); }

auto GLVertexArray::Unbind() const -> void { glBindVertexArray(0); }
