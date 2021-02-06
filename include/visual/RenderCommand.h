#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <string>

class Engine;
struct GLFWwindow;

class RenderCommand
{
public:

    static auto SetClearColor(glm::vec4 const& color) -> void;
    static auto GetClearColor() -> glm::vec4;
    static auto ClearDisplay() -> void;

    static auto ImGuiNewFrame() -> void;
    static auto Display() -> void;

    static auto GetScreenSize() -> glm::uvec2;

private:

    static auto Init(uint32_t width, uint32_t height, std::string const& title) -> GLFWwindow*;
    static auto Terminate() -> void;

private:

    static glm::uvec2 m_ScreenSize;
    static glm::vec4 m_ClearColor;

    friend Engine;
};
