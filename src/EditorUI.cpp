#include "EditorUI.h"
#include "Editor.h"

bool EditorUI::showInfo = false;

EditorUI::EditorUI() = default;

EditorUI::~EditorUI() = default;

void EditorUI::mainMenuBar() {
    // Menu bar
    if ( ImGui::BeginMainMenuBar() ) {
        if ( ImGui::BeginMenu("File") ) {
            if ( ImGui::MenuItem("New") ) {  }
            if ( ImGui::MenuItem("Open", "Ctrl+O") ) {  }
            if ( ImGui::MenuItem("Save", "Ctrl+S") ) {  }
            if ( ImGui::MenuItem("Save As..") ) { }

            ImGui::Separator();

            if ( ImGui::MenuItem("Options") ) { showInfo = !showInfo; }

            if ( ImGui::MenuItem("Quit", "Alt+F4") ) { Editor::editorIsRunning = false; }

            ImGui::EndMenu();
        }

        if ( ImGui::BeginMenu("Edit") ) {
            if ( ImGui::MenuItem("Undo", "CTRL+Z") ) {  }
            if ( ImGui::MenuItem("Redo", "CTRL+Y", false, false) ) {}  // Disabled item

            ImGui::Separator();

            if ( ImGui::MenuItem("Cut", "CTRL+X") ) {  }
            if ( ImGui::MenuItem("Copy", "CTRL+C") ) {  }
            if ( ImGui::MenuItem("Paste", "CTRL+V") ) {  }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    getInfo(showInfo);
}

void EditorUI::getInfo(const bool& _open) {
    if ( _open ) {
        // Create a window called "Hello, world!" and append into it.
        ImGui::Begin("Version of GLFW, GLSL and OpenGL");

        // Display some text (you can use a format strings too)
        // GLFW Version
        ImGui::Text("GLFW version: %d,%d,%d", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION );

        // glGetString returns a pointer to a static string describing some aspect of the current GL connection.
        // Returns the company responsible for this GL implementation. This name does not change from release to release.
        ImGui::Text("OpenGL version: %s", glGetString(GL_VERSION) );

        // Returns a version or release number for the shading language.
        ImGui::Text("GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION) );

        // Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release.
        ImGui::Text("Vendor: %s", glGetString(GL_VENDOR) );

        // Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release.
        ImGui::Text("Renderer: %s", glGetString(GL_RENDERER) );

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}