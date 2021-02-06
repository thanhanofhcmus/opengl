cmake_minimum_required(VERSION 3.12)

add_library(imgui
     imgui.cpp
     imgui_demo.cpp
     imgui_draw.cpp
     imgui_internal.h
     imgui_tables.cpp
     imgui_widgets.cpp
     backends/imgui_impl_glfw.cpp
     backends/imgui_impl_opengl3.cpp
    )

target_link_libraries(imgui PRIVATE glad)

target_include_directories(imgui
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

