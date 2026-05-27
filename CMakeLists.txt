cmake_minimum_required(VERSION 4.0)
project(transport-flu LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE tf-source "src/*.cpp")

add_executable(tf ${tf-source})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(tf PUBLIC TF_BUILD_RELEASE)
else()
    target_compile_definitions(tf PUBLIC TF_BUILD_DEBUG)
endif()

find_package(OpenGL REQUIRED)

add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(tf PUBLIC GLFW_INCLUDE_NONE)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/spdlog)
set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(spdlog PUBLIC SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)

target_link_libraries(tf PUBLIC
        OpenGL::GL
        glad
        glfw
        glm
        spdlog
        dl
        pthread
)
