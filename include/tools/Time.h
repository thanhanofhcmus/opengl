#pragma once

#include <chrono>

class Engine;

class Time
{
public:

    static auto Delta() -> float;

    static auto Total() -> float;

private:

    static auto InternalUpdate() -> void;

private:

    static std::chrono::high_resolution_clock::time_point m_Start;
    static std::chrono::high_resolution_clock::time_point m_Last;
    static float m_Delta;
    static float m_Total;

    friend Engine;
};
