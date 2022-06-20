cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set main project
project(app VERSION 1.0)

# `app` sources
file(GLOB_RECURSE APP_SRCS src/*.cpp)
add_executable(app ${APP_SRCS})

# Setup OpenGL
target_include_directories(app PUBLIC ${GL_INCLUDE_DIRS})
target_link_libraries(app PUBLIC GL)

