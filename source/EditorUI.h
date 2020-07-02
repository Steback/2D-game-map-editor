#ifndef EDITOR_UI_H
#define EDITOR_UI_H

#include <utility>
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glm/glm.hpp"

class Entity;
class TextureManager;

class EditorUI {
    public:
        explicit EditorUI(ImGuiIO& _io);
        ~EditorUI();
        void initialized(GLFWwindow* _window);
        void updateMouseInput();
        void selectEntity(glm::vec2 _mousePos);
        void mainMenuBar();
        void entitiesPanel();
        void proprietiesPanel();
        void tilesMapPanel();
        void getVersions();
        void renderUI();

        Entity* entitySelected;
        std::pair<std::string, std::shared_ptr<TextureManager> > tileSelected;

    private:
        ImGuiIO& io;
        ImGuiStyle& style = ImGui::GetStyle();
        ImGuiWindowFlags windowFlags{};
        bool showInfo{};
        bool createEntity{};
        std::vector<unsigned int> entitiesID;
        std::vector<std::string> layerTypes = { "VEGETATION_LAYER", "ENEMY_LAYER", "OBSTACLE_LAYER", "PLAYER_LAYER" };
};

#endif