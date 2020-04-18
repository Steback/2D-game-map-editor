#ifndef EDITOR_UI_H
#define EDITOR_UI_H

#include "../lib/imgui/imgui.h"

class EditorUI {
    public:
        EditorUI();
        ~EditorUI();
        static void mainMenuBar(float& _x, float& _y);
        static void assetsPanel(float& _x, float& _y, ImGuiWindowFlags _windowFlags);
        static void statsPanel(float& _x, float& _y, ImGuiWindowFlags _windowFlags);
        static void getVersions(bool& _open, float& _x, float& _y);

    private:
        static bool showInfo;
};

#endif