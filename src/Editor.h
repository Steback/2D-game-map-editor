#ifndef EDITOR_H
#define EDITOR_H

// Dear ImGui
#include "../lib//imgui/imgui.h"
#include "../lib/imgui_glfw/imgui_impl_glfw.h"
#include "../lib//imgui/imgui_impl_opengl3.h"

// OpenGL Math(GLM)
#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"

// OpenGL loader
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

class Editor {
    public:
        explicit Editor(ImGuiIO& _io);
        ~Editor();
        bool isRunning();
        void initialized(const int& _width, const int& _height);
        void processInput();
        void renderUI();
        void render();
        void destroy();

    private:
        bool editorIsRunning;

        // Create window with graphics context
        GLFWwindow* window{};

        ImGuiIO io;

};

#endif