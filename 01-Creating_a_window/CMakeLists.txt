cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set main project
project(app VERSION 1.0)

# `app` sources
file(GLOB_RECURSE APP_SRCS targets/app/*.cpp)
add_executable(app ${APP_SRCS})

# Setup `example-lib` library
add_subdirectory(libs/example-lib)
target_include_directories(app PUBLIC ${EXLIB_INCLUDE_DIR})
target_link_libraries(app PUBLIC exlib)

# Setup OpenGL
target_include_directories(app PUBLIC ${GL_INCLUDE_DIRS})
target_link_libraries(app PUBLIC GL)

# Setup Catch2 along with tests
add_subdirectory(libs/Catch2)
add_executable(tests targets/tests/wnd-size.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE ${EXLIB_INCLUDE_DIR})
target_link_libraries(tests PRIVATE exlib)

