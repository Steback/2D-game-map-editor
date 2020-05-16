cmake_minimum_required(VERSION 3.15)
project(2D_Game_Map_Editor)

set(CMAKE_CXX_STANDARD 20)

find_library(GLEW REQUIRED)
find_library(glfw REQUIRED)
find_library(OpenGL REQUIRED)

file(GLOB SOURCE_FILES ./src/*.cpp )

# Dear ImGui
file(GLOB IMGUI_SOURCE ./lib/imgui/ImGui/*.cpp )
include_directories( ${PROJECT_SOURCE_DIR}/lib/imgui/ )

# stb_image
include_directories( ${PROJECT_SOURCE_DIR}/lib/stb/ )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCE} )
target_link_libraries( ${PROJECT_NAME} glfw GLEW OpenGL )

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR} )

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "Editor"
        SUFFIX ".o"
)