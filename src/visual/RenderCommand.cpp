#include <visual/RenderCommand.h>
#include <Engine.h>

#include <Log.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imconfig.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

glm::uvec2 RenderCommand::m_ScreenSize{};
glm::vec4 RenderCommand::m_ClearColor{ 0.0f, 0.0f, 0.0f, 1.0f };

auto RenderCommand::Init(uint32_t width, uint32_t height, std::string const& title) -> GLFWwindow*
{
     if (!glfwInit())
    {
        LOG_ERROR("GLFW init failed");
        std::terminate();
    }
    LOG_INFO("GLFW Init complete");
    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    // Hinting it core profile causes error
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window)
    {
        LOG_ERROR("GLFW create window failed");
        glfwTerminate();
        std::terminate();
    }
    LOG_INFO("GLFW Window Init complete");
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //Enable Vsync
    // glViewport(0, 0, width, height);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("GLAD init failed");
        std::terminate();
    }
    LOG_INFO("Init complete");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    m_ScreenSize = { width, height };

    return window;
}

auto RenderCommand::Terminate() -> void
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(Engine::GetNativeWindow());
    glfwTerminate();
}

auto RenderCommand::GetScreenSize() -> glm::uvec2 { return m_ScreenSize; }

auto RenderCommand::SetClearColor(glm::vec4 const& color) -> void
{
    glClearColor(color.r, color.g, color.b, color.a);
    m_ClearColor = color;
}

auto RenderCommand::GetClearColor() -> glm::vec4 { return m_ClearColor; }

auto RenderCommand::ClearDisplay() -> void { glClear(GL_COLOR_BUFFER_BIT); }

auto RenderCommand::ImGuiNewFrame() -> void
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

auto RenderCommand::Display() -> void {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(Engine::GetNativeWindow());
}
