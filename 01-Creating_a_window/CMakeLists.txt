cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set main project
project(app VERSION 1.0)

# `app` sources
file(GLOB_RECURSE APP_SRCS src/*.cpp)
add_executable(app ${APP_SRCS})

# Setup GLFW and OpenGL
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
target_link_libraries(app glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(app OpenGL::GL)

# Setup GLAD
add_subdirectory(lib/glad/cmake glad_cmake)
glad_add_library(glad_gl_core_mx_33 STATIC MX API gl:core=3.3)
target_link_libraries(app glad_gl_core_mx_33)

