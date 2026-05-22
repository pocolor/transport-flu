cmake_minimum_required(VERSION 4.0)
project(transport-flu LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE engine_source "engine/src/*.cpp")
file(GLOB_RECURSE game_source "game/src/*.cpp")

add_library(engine SHARED ${engine_source})
add_executable(game ${game_source})

target_include_directories(engine PUBLIC engine/include)
target_include_directories(game PUBLIC game/include)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(engine PUBLIC TF_BUILD_RELEASE)
else()
    target_compile_definitions(engine PUBLIC TF_BUILD_DEBUG)
endif()

find_package(OpenGL REQUIRED)

add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(engine PUBLIC GLFW_INCLUDE_NONE)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/spdlog)
set_target_properties(spdlog PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(spdlog PUBLIC SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)

target_link_libraries(engine PUBLIC
        OpenGL::GL
        glad
        glfw
        glm
        spdlog
        dl
        pthread
)

target_link_libraries(game PRIVATE engine)
