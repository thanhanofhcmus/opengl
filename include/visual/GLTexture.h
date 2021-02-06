#pragma once

#include <string>

class GLTexture
{
public:

    GLTexture();
    GLTexture(std::string const& filename);

    auto LoadImage(std::string const& filename) -> void;

    auto GetIndex() const -> int;

    auto Bind() const -> void;
    auto Unbind() const -> void;

private:

    uint32_t m_ID;
    int m_Index;

    static int m_IndexCounter;
};
