cmake_minimum_required(VERSION 3.15)
project(2D_Game_Map_Editor)

set(CMAKE_CXX_STANDARD 20)

find_library(GLEW REQUIRED)
find_library(glfw REQUIRED)
find_library(OpenGL REQUIRED)

file(GLOB SOURCE_FILES ./src/*.cpp )
file(GLOB IMGUI_SOURCE ./lib/imgui/*.cpp )
file(GLOB IMGUI_GLFW_SOURCE ./lib/imgui_glfw/*.cpp )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCE} ${IMGUI_GLFW_SOURCE} )
target_link_libraries( ${PROJECT_NAME} glfw GLEW OpenGL )

set(EXECUTABLE_OUTPUT_PATH "..")

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}"
        SUFFIX ".o"
)