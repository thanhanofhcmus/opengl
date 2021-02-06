#include <tools/Resource.h>
#include <config.h>
#include <assert.h>

std::string Resource::m_Base 		  = PATH_RESOURCES;
std::string Resource::m_ShaderScript  = PATH_RESOURCES + DIR_SHADER_SCRIPTS;
std::string Resource::m_Texture       = PATH_RESOURCES + DIR_TEXTURE;

auto Resource::GetPath(std::string const& filename, ResourceLocation loc) -> std::string
{
    switch (loc)
    {
    case ResourceLocation::ShaderScript: return (m_ShaderScript + filename);
    case ResourceLocation::Texture:		return (m_Texture + filename);
    }
    assert(false);
}
