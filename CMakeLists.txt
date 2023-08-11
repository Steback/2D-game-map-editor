cmake_minimum_required(VERSION 3.15)
project(2D_Game_Map_Editor)

### Settings ###
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)

### Dependencies ###
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(stb REQUIRED)
find_package(imgui REQUIRED)
find_package(tinyxml2 REQUIRED)
find_package(fmt REQUIRED)
find_package(lua REQUIRED)
find_package(sol2 REQUIRED)

# ImGui Bindings ###
include_directories(bindings)
file(GLOB BINDINGS_SOURCE_FILES ${PROJECT_SOURCE_DIR}/bindings/*.cpp)

### Source Files ###
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)

### Executable ###
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${BINDINGS_SOURCE_FILES})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "Editor"
)

target_link_libraries(${PROJECT_NAME}
        opengl::opengl
        GLEW::GLEW
        glfw
        imgui::imgui
        glm::glm
        stb::stb
        tinyxml2::tinyxml2
        fmt::fmt
        lua::lua
        sol2::sol2)
