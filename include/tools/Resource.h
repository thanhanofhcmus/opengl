#pragma once

#include <string>

enum class ResourceLocation
{
    Texture,
    ShaderScript,
};

class Resource
{
public:

    static auto GetPath(std::string const& filename, ResourceLocation loc) -> std::string;

private:

    static std::string m_Base;
    static std::string m_Texture;
    static std::string m_ShaderScript;
};
