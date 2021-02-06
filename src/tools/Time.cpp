#include <tools/Time.h>

std::chrono::high_resolution_clock::time_point Time::m_Start = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point Time::m_Last = m_Start;
float Time::m_Delta = 0.0f;
float Time::m_Total = 0.0f;

auto Time::Delta() -> float { return m_Delta; }

auto Time::Total() -> float { return m_Total; }

auto Time::InternalUpdate() -> void
{
    auto now = std::chrono::high_resolution_clock::now();
    m_Delta = (now - m_Last).count();
    m_Total = (now - m_Start).count();
    m_Last = now;
}
