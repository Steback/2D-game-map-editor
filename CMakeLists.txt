cmake_minimum_required(VERSION 3.15)
project(2D_Game_Map_Editor)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)

# Dear ImGui source files
file(GLOB IMGUI_SOURCE ${PROJECT_SOURCE_DIR}/lib/imgui/*.cpp )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCE} )

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR} )

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "Editor"
)

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

include_directories(
        # stb-image
        ${PROJECT_SOURCE_DIR}/lib/stb

        # ImGui
        ${PROJECT_SOURCE_DIR}/lib/imgui
)

# GLM
add_subdirectory( ${PROJECT_SOURCE_DIR}/lib/glm )

#  TinyXML2
add_subdirectory( ${PROJECT_SOURCE_DIR}/lib/tinyxml2 )

target_link_libraries( ${PROJECT_NAME}
        OpenGL
        GLEW
        glfw
        glm
        tinyxml2
        )