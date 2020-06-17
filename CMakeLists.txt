cmake_minimum_required(VERSION 3.15)
project(2D_Game_Map_Editor)

set(CMAKE_CXX_STANDARD 17)

# Editor Source Files
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)

# Dear ImGui Source Files
file(GLOB IMGUI_SOURCE ${PROJECT_SOURCE_DIR}/lib/imgui/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCE})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "Editor"
)

# stb_image
include_directories(${PROJECT_SOURCE_DIR}/lib/stb)

# Dear Imgui
include_directories(${PROJECT_SOURCE_DIR}/lib/imgui)

# GLFW
find_library(glfw3 REQUIRED)

# OpenGL
find_library(OpenGL REQUIRED)

# GLEW
find_library(GLEW REQUIRED)

# GLM
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glm)

#  TinyXML2
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/tinyxml2)

target_link_libraries(${PROJECT_NAME}
        OpenGL
        GLEW
        glfw
        glm
        tinyxml2
        )