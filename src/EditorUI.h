#ifndef EDITOR_UI_H
#define EDITOR_UI_H

class EditorUI {
    public:
        EditorUI();
        ~EditorUI();
        static void mainMenuBar();
        static void assetsPanel(float& _x, float& _y);
        static void statsPanel(float& _x, float& _y);
        static void getInfo(const bool& _open);

    private:
        static bool showInfo;
};

#endif