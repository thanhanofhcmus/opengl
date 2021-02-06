#pragma once

#include <cstdint>

enum class GLBufferType
{
    Invalid = -1,
    Vertex  = 0x8892,
    Index   = 0x8893,
};

enum class GLDataType
{
    Invalid = -1,
    Byte    = 0x1400,
    UByte   = 0x1401,
    Short   = 0x1402,
    UShort  = 0x1403,
    Int     = 0x1404,
    UInt    = 0x1405,
    Float   = 0x1406,
};

enum class GLShaderType
{
    Invalid = -1,
    Fragment = 0x8B30,
    Vertex   = 0x8B31,
};

enum class GLDrawPrimitiveType
{
    Invalid       = -1,
    Points        = 0x0000,
    Lines         = 0x0001,
    LineLoop      = 0x0002,
    LineStrip     = 0x0003,
    Triangles     = 0x0004,
    TriangleStrip = 0x0005,
    TriangleFan   = 0x0006,
};

auto GLGetDataSize(GLDataType type) -> uint32_t;
