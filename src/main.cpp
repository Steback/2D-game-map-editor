#include "Editor.h"
#include "Constants.h"

int main(int, const char**) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    auto* editor = new Editor(io);

    editor->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while ( editor->isRunning() ) {
        editor->processInput();
        editor->update();
        editor->render();
    }

    editor->destroy();

    delete editor;

    return 0;
}