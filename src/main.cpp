#include "Editor.h"

int main(int, char**) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    auto* editor = new Editor(io);

    editor->initialized();

    // Main loop
    while ( editor->isRunning() ) {
        editor->processInput();
        editor->render();
    }

    editor->destroy();

    delete editor;

    return 0;
}