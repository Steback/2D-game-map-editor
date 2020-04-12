#ifndef EDITOR_H
#define EDITOR_H

// Dear ImGui
#include "../lib//imgui/imgui.h"
#include "../lib/imgui_glfw/imgui_impl_glfw.h"
#include "../lib//imgui/imgui_impl_opengl3.h"

// OpenGL loader
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

class EditorUI;

class Editor {
    public:
        explicit Editor(ImGuiIO& _io);
        ~Editor();
        static bool isRunning();
        void initialized(const int& _width, const int& _height);
        void processInput();
        void renderUI();
        void render();
        void destroy();

        friend class EditorUI;

    private:
        static bool editorIsRunning;

        // Create window with graphics context
        GLFWwindow* window{};

        ImGuiIO& io;
        int displayWidth{};
        int displayHeight{};
};

#endif