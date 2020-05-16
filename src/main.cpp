#include "Editor.h"

int main(int, char**) {
    std::unique_ptr<Editor> editor = std::make_unique<Editor>();

    editor->initialized();

    // Main loop
    while ( !editor->isRunning() ) {
        editor->update();
        editor->render();
    }

    editor->destory();

    return 0;
}