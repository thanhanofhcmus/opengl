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
    layout (location = 1) in vec3 a_Color;
    layout (location = 2) in vec2 a_TexCoord;
    out vec3 v_Color;
    out vec2 v_TexCoord;
    uniform mat4 u_MVP;
    void main()
    {
        gl_Position = u_MVP * vec4(a_Pos, 0.0f, 1.0f);
        v_Color = a_Color;
        v_TexCoord = a_TexCoord;
    })";

    std::string fragment_source =
    R"(#version 460 core
    in vec3 v_Color;
    in vec2 v_TexCoord;
    out vec4 FragColor;
    uniform sampler2D u_Tex0;
    uniform sampler2D u_Tex1;
    uniform float 	  u_Mix;
    void main()
    {
        FragColor = vec4(v_Color, 1.0f) * mix(texture(u_Tex0, v_TexCoord), texture(u_Tex1, v_TexCoord), u_Mix);
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

    GLTexture tex0("wall.jpg");
    GLTexture tex1("container.jpg");

    shader.SendUniform1i("u_Tex0", tex0.GetIndex());
    shader.SendUniform1i("u_Tex1", tex1.GetIndex());

    glm::mat4 camera = glm::ortho(-HWIDTH, HWIDTH, -HHEIGHT, HHEIGHT);
    float u_Mix = 0.5f;
    float degree = 0.0f;

    while (Engine::IsRunning())
    {
        Engine::PollEvent();
        RenderCommand::ImGuiNewFrame();

        if (Keyboard::IsKeyPressed(Keycode::Escape) || Keyboard::IsKeyPressed(Keycode::Q))
            Engine::Close();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Cube");
        ImGui::SliderFloat("Mixture", &u_Mix, 0.0f, 1.0f);
        shader.SendUniform1f("u_Mix", u_Mix);
        ImGui::End();

        degree = Keyboard::Input2Degree(Keycode::A, Keycode::D, degree, 5.0f);
        glm::mat4 mvp(1.0f);
        mvp = glm::rotate(mvp, glm::radians(degree), glm::vec3(0.0f, 0.0f, 1.0f));
        mvp = glm::scale(mvp, glm::vec3(400.0f));
        mvp = camera * mvp;
        shader.SendUniformMatrix4f("u_MVP", mvp);

        RenderCommand::ClearDisplay();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        RenderCommand::Display();
    }

    Engine::Terminate();
}
