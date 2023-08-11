#include "Editor.h"

int main(int, char**) {
    Editor editor;

    editor.initialized();

    while ( !editor.isRunning() ) {
        editor.render();
    }

    editor.destroy();

    return 0;
}