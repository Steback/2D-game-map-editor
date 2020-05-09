#ifndef EDITOR_UI_H
#define EDITOR_UI_H

// Dear ImGui
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui_impl_glfw.h"
#include "../lib/imgui/imgui_impl_opengl3.h"

class EditorUI {
    public:
        explicit EditorUI(ImGuiIO& _io);
        ~EditorUI();
        void initialized(GLFWwindow* _window);
        void renderUI();
        void mainMenuBar();
        void entitiesPanel() const;
        void statsPanel() const;
        void getVersions();

    private:
        ImGuiIO& io;
        ImGuiStyle& style = ImGui::GetStyle();
        ImGuiWindowFlags windowFlags{};
        bool showInfo{};
};

#endif