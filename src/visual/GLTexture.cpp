#include <visual/GLTexture.h>
#include <Log.h>
#include <glad/glad.h>
#include <visual/stb_image.h>
#include <tools/Resource.h>

int GLTexture::m_IndexCounter = 0;

GLTexture::GLTexture()
{
    glGenTextures(1, &m_ID);
    m_Index = m_IndexCounter++;

    // Defaulted for now
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

GLTexture::GLTexture(std::string const& filename)
{
    glGenTextures(1, &m_ID);
    m_Index = m_IndexCounter++;

    // Defaulted for now
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    LoadImage(filename);
}

auto GLTexture::LoadImage(std::string const& filename) -> void
{
    Bind();
    int width, height, channels;
    std::string path = Resource::GetPath(filename, ResourceLocation::Texture);
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data)
        LOG_WARN("Cannot find resouce: {}", path);
    else
    {
        // Default lots of things for now
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
}

auto GLTexture::GetIndex() const -> int { return m_Index; }

auto GLTexture::Bind() const -> void
{
    glActiveTexture(GL_TEXTURE0 + m_Index);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

auto GLTexture::Unbind() const -> void { glBindTexture(GL_TEXTURE_2D, 0); }
