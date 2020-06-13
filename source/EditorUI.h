#ifndef EDITOR_UI_H
#define EDITOR_UI_H

#include <vector>

// Dear ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class EditorUI {
    public:
        explicit EditorUI(ImGuiIO& _io);
        ~EditorUI();
        void initialized(GLFWwindow* _window);
        void renderUI();
        void mainMenuBar();
        void entitiesPanel();
        void proprietiesPanel();
        void tilesMapPanel() const;
        void getVersions();

    private:
        ImGuiIO& io;
        ImGuiStyle& style = ImGui::GetStyle();
        ImGuiWindowFlags windowFlags{};
        bool showInfo{};
        bool createEntity{};
        std::vector<std::pair<unsigned int, std::string> > entitiesID;
};

#endif