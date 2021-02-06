#include <visual/GLEnums.h>
#include <assert.h>

auto GLGetDataSize(GLDataType type) -> uint32_t
{
    switch (type)
    {
    case GLDataType::Byte   : return  1;
    case GLDataType::UByte  : return  1;
    case GLDataType::Short  : return  2;
    case GLDataType::UShort : return  2;
    case GLDataType::Int    : return  4;
    case GLDataType::UInt   : return  4;
    case GLDataType::Float  : return  4;

    default:
        assert(false);
    }
}
