#include <Engine.h>
#include <Log.h>

#include <visual/RenderCommand.h>
#include <tools/Time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* Engine::m_Window = nullptr;
std::string Engine::m_Title{"TITLE"};

auto Engine::Init(size_t width, size_t height, std::string const& title) -> void
{
    spdlog::set_pattern("%^[%l] [%!] [%#]%$: %v");

    m_Title = title;
    m_Window = RenderCommand::Init(width, height, title);
}

auto Engine::Terminate() -> void { RenderCommand::Terminate(); }

auto Engine::IsRunning() -> bool { return !glfwWindowShouldClose(m_Window); }

auto Engine::InternalUpdate() -> void
{
    Time::InternalUpdate();
}

auto Engine::Close() -> void { glfwSetWindowShouldClose(m_Window, true); }

auto Engine::PollEvent() -> void { glfwPollEvents(); }

auto Engine::GetNativeWindow() -> GLFWwindow* { return m_Window; }

auto Engine::GetTitle() -> std::string { return m_Title; }
