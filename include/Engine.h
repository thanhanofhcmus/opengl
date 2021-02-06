#pragma once

#include <string>

struct GLFWwindow;

class Engine
{
public:

    static auto Init(size_t width, size_t height, std::string const& title) -> void;
    static auto Terminate() -> void;

    static auto PollEvent() -> void;
    static auto InternalUpdate() -> void;

    static auto GetNativeWindow() -> GLFWwindow*;

    static auto GetTitle() -> std::string;

    static auto IsRunning() -> bool;
    static auto Close() -> void;

private:

    static GLFWwindow* m_Window;
    static std::string m_Title;
};
