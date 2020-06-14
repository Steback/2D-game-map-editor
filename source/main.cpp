#include "Editor.h"

int main(int, char**) {
    Editor editor;

    editor.initialized();

    while ( !editor.isRunning() ) {
        editor.update();
        editor.render();
    }

    editor.destroy();

    return 0;
}