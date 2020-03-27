cmake_minimum_required(VERSION 3.15)
project(2D_Game_Map_Editor)

set(CMAKE_CXX_STANDARD 14)

find_library(SDL2 REQUIRED)
find_library(GLEW REQUIRED)
find_library(OpenGL REQUIRED)
#add_library( gl3w lib/GL/gl3w.c lib/GL/gl3w.h )

file(GLOB HEADER_FILES ./src/*.h )
file(GLOB SOURCE_FILES ./src/*.cpp )
file(GLOB IMGUI_SOURCE ./lib/imgui/*.cpp )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${IMGUI_SOURCE} )
target_link_libraries( ${PROJECT_NAME} SDL2 GLEW OpenGL ${CMAKE_DL_LIBS} )

set(EXECUTABLE_OUTPUT_PATH "..")

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}"
        SUFFIX ".o"
)