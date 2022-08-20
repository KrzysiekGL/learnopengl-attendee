cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_INIT "-Wall")

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
add_subdirectory(lib/glad)
target_include_directories(app PRIVATE ${GLAD_33_INCLUDE_DIR})
target_link_libraries(app glad_33)

# Setup GLM
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/glm)

