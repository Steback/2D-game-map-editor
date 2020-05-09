#ifndef EDITOR_H
#define EDITOR_H

#include <vector>

// Dear ImGui
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui_impl_glfw.h"
#include "../lib/imgui/imgui_impl_opengl3.h"

// OpenGL loader
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#include "Window.h"
#include "EditorUI.h"
#include "Camera.h"

class Mesh;
class Shader;

class AssetsManager;
class EntityManager;

class Editor {
    public:
        explicit Editor(ImGuiIO& _io);
        ~Editor();
        void initialized();
        bool isRunning();
        void render();
        void destory();

    private:
        Window window;
        EditorUI ui;
        Camera camera;
        std::vector<Shader*> shaders;
        std::vector<Mesh*> mesh;
};

#endif