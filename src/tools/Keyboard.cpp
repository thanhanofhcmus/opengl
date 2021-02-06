#include <tools/Keyboard.h>
#include <Engine.h>
#include <GLFW/glfw3.h>

auto Keyboard::IsKeyPressed(Keycode key) -> bool
{
    return glfwGetKey(Engine::GetNativeWindow(), static_cast<int>(key)) == GLFW_PRESS;
}

auto Keyboard::IsKeyReleased(Keycode key) -> bool
{
    return glfwGetKey(Engine::GetNativeWindow(), static_cast<int>(key)) == GLFW_RELEASE;
}
