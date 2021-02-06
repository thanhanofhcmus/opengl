cmake_minimum_required(VERSION 3.12)

project(test LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -g -fsanitize=address")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(cmake/ResourceConfig.cmake)

configure_file(include/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

add_subdirectory(vendors)
add_subdirectory(src)
