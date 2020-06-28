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

# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glew-cmake)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glfw)

# GLM
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glm)

# stb_image
include_directories(${PROJECT_SOURCE_DIR}/lib/stb)

# Dear Imgui
include_directories(${PROJECT_SOURCE_DIR}/lib/imgui)

#  TinyXML2
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/tinyxml2)

target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        GLEW
        glfw
        glm
        tinyxml2
        )