#include "Editor.h"
#include "Constants.h"

int main() {
    auto* editor = new Editor();

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
