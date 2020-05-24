cmake_minimum_required(VERSION 3.15)
project(2D_Game_Map_Editor)

set(CMAKE_CXX_STANDARD 20)

find_library(OpenGL REQUIRED)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)

# Dear ImGui source files
file(GLOB IMGUI_SOURCE ${PROJECT_SOURCE_DIR}/lib/imgui/*.cpp )

include_directories(
        ${PROJECT_SOURCE_DIR}/lib/stb
        ${PROJECT_SOURCE_DIR}/lib/imgui
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory( ${PROJECT_SOURCE_DIR}/lib/glfw )

add_subdirectory( ${PROJECT_SOURCE_DIR}/lib/glm )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCE} )
target_link_libraries( ${PROJECT_NAME} OpenGL GLEW glfw glm )

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR} )

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "Editor"
)