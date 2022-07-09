# glad permalink: https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on
add_library(glad_33 src/glad.c)
set(GLAD_33_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(glad_33 PUBLIC ${GLAD_33_INCLUDE_DIR})

