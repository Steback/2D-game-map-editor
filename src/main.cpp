#include "Editor.h"

int main(int, char**) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    Editor editor(io);

    editor.initialized();

    // Main loop
    while ( !editor.isRunning() ) {
        editor.render();
    }

    editor.destory();

    return 0;
}