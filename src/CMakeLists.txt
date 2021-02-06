cmake_minimum_required(VERSION 3.12)

set(glm_DIR ${PROJECT_SOURCE_DIR}/vendors/glm/cmake/glm)
find_package(glm REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(spdlog REQUIRED)

add_executable(test
    main.cpp
    Engine.cpp

    visual/GLEnums.cpp
    visual/GLBuffers.cpp
    visual/GLVertexArray.cpp
    visual/GLShader.cpp
    visual/GLTexture.cpp
    visual/RenderCommand.cpp
    visual/stb_image.cpp

    tools/Time.cpp
    tools/Keyboard.cpp
    tools/Resource.cpp
    )

target_link_libraries(test PRIVATE imgui glm::glm glad glfw OpenGL::GL spdlog::spdlog)
target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/include)
