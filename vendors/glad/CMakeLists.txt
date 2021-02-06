cmake_minimum_required(VERSION 3.12)

add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)
target_link_libraries(glad PRIVATE ${CMAKE_DL_LIBS})
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
