#include <iostream>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Engine.h>
#include <tools/Keyboard.h>
#include <tools/Resource.h>

#include <visual/GLTools.h>

#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

int main()
{
    int constexpr WIDTH = 1000;
    int constexpr HEIGHT = 800;
    char const* TITLE = "TITLE";
    float constexpr HWIDTH = WIDTH / 2;
    float constexpr HHEIGHT = HEIGHT / 2;

    Engine::Init(WIDTH, HEIGHT, TITLE);
    RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });

    std::string vertex_source =
    R"(#version 460 core
    layout (location = 0) in vec2 a_Pos;
    layout (location = 2) in vec2 a_TexCoord;
    out vec2 v_TexCoord;
    uniform mat4 u_MVP;
    void main()
    {
        gl_Position = u_MVP * vec4(a_Pos, 0.0f, 1.0f);
        v_TexCoord = a_TexCoord;
    })";

    std::string fragment_source =
    R"(#version 460 core
    in vec2 v_TexCoord;
    out vec4 FragColor;
    uniform sampler2D u_Tex1;
    void main()
    {
        FragColor = texture(u_Tex1, v_TexCoord);
    })";

    float vertices[] =
    {
        -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    };

    uint32_t indicies[] =
    {
        0, 1, 2,
        0, 3, 2,
    };

    GLVertexArray va;
    va.Bind();

    GLBuffer vb(vertices, sizeof(vertices) / sizeof(float), GLDataType::Float, GLBufferType::Vertex);
    GLBuffer ib(indicies, sizeof(indicies) / sizeof(uint32_t), GLDataType::UInt, GLBufferType::Index);

    va.SetLayout(
    {
        { GLDataType::Float, 2 },
        { GLDataType::Float, 3 },
        { GLDataType::Float, 2 }
    });

    GLShader shader;
    shader.LoadFromMemory(vertex_source, fragment_source);
    shader.Bind();

    GLTexture tex1("container.jpg");

    shader.SendUniform1i("u_Tex1", tex1.GetIndex());

    glm::mat4 proj = glm::ortho(-HWIDTH, HWIDTH, -HHEIGHT, HHEIGHT);
    glm::mat4 view = glm::mat4(1.0f);
    float degree = 0.0f;
    glm::vec3 pos1(0.0f);
    glm::vec3 pos2(0.0f);

    glm::vec4 color;

    while (Engine::IsRunning())
    {
        Engine::PollEvent();
        RenderCommand::ImGuiNewFrame();

        if (Keyboard::IsKeyPressed(Keycode::Escape) || Keyboard::IsKeyPressed(Keycode::Q))
            Engine::Close();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Position");
        ImGui::SliderAngle("Angle 1", &degree);
        ImGui::SliderFloat3("Position 1", &pos1.x, -HWIDTH, HWIDTH);
        ImGui::SliderFloat3("Position 2", &pos2.x, -HWIDTH, HWIDTH);
        ImGui::ColorPicker3("Clear color", &color.r);
        ImGui::End();

        RenderCommand::SetClearColor(color);

        RenderCommand::ClearDisplay();

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, pos1);
            model = glm::scale(model, glm::vec3(400.0f));
            model = glm::rotate(model, degree, glm::vec3(0.0f, 0.0f, 1.0f));
            shader.SendUniformMatrix4f("u_MVP", proj * view * model);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, pos2);
            model = glm::scale(model, glm::vec3(400.0f));
            shader.SendUniformMatrix4f("u_MVP", proj * view * model);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }



        RenderCommand::Display();
    }

    Engine::Terminate();
}
