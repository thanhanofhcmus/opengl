#pragma once

#include <tools/Keycode.h>

class Keyboard
{
public:

    static auto IsKeyPressed(Keycode key) -> bool;
    static auto IsKeyReleased(Keycode key) -> bool;

    template <typename T>
    static auto Input2Degree(Keycode inc, Keycode dec, T const& init, T const& offset) -> T;
};

template <typename T>
auto Keyboard::Input2Degree(Keycode inc, Keycode dec, T const& init, T const& offset) -> T
{
    T val = init;
    if (IsKeyPressed(inc))
        val = val + offset;
    if (IsKeyPressed(dec))
        val = val - offset;
    return val;
}
