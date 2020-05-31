#include <iostream>

#include "EditorUI.h"
#include "Window.h"

EditorUI::EditorUI(ImGuiIO& _io) : io(_io) {  }

EditorUI::~EditorUI() = default;

void EditorUI::initialized(GLFWwindow* _window) {
    // TODO: Setup Dear ImGui style
    ImGui::StyleColorsDark();
    style.WindowBorderSize = 0.0f;
    style.WindowRounding = 0;
    style.WindowPadding = ImVec2(10, 15);

    std::string glsl_version = "#version 330";

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    // TODO: Load Font
    io.Fonts->AddFontFromFileTTF("assets/fonts/Karla-Regular.ttf", 16.0f);

    // TODO: Window flags
    windowFlags |= ImGuiWindowFlags_NoTitleBar;
    windowFlags |= ImGuiWindowFlags_NoResize;
}

void EditorUI::renderUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    mainMenuBar();
    entitiesPanel();
    statsPanel();

    ImGui::Render();
}

void EditorUI::mainMenuBar() {
    // Menu bar
    if ( ImGui::BeginMainMenuBar() ) {
        if ( ImGui::BeginMenu("File") ) {
            if ( ImGui::MenuItem("New") ) {  }
            if ( ImGui::MenuItem("Open", "Ctrl+O") ) {  }
            if ( ImGui::MenuItem("Save", "Ctrl+S") ) {  }
            if ( ImGui::MenuItem("Save As..") ) { }

            ImGui::Separator();

            if ( ImGui::MenuItem("Options") ) {  }
            if ( ImGui::MenuItem("Versions") ) { showInfo = !showInfo; }
            if ( ImGui::MenuItem("Quit", "Alt+F4") ) {  }

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

    getVersions();
}

void EditorUI::entitiesPanel() const {
    ImGui::SetNextWindowPos(ImVec2(0,22), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, io.DisplaySize.y - 22), ImGuiCond_Always);
    ImGui::Begin("Entities", nullptr, windowFlags);

    if( ImGui::Button("Add Entity") ) {
        // TODO: Create Entities

    }

    ImGui::End();
}

void EditorUI::statsPanel() const {
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - 200,22), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, io.DisplaySize.y - 22), ImGuiCond_Always);
    ImGui::Begin("Stats", nullptr, windowFlags);

    ImGui::End();
}

void EditorUI::getVersions() {
    if ( showInfo ) {
        ImGui::SetNextWindowPos(ImVec2((io.DisplaySize.x / 2) - 145, (io.DisplaySize.y / 2) - 80), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(290, 160), ImGuiCond_Always);

        ImGui::Begin("Version of GLFW, GLSL and OpenGL", &showInfo, ImGuiWindowFlags_NoResize);
            ImGui::Text("GLFW version: %d,%d,%d", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION );
            ImGui::Text("OpenGL version: %s", glGetString(GL_VERSION) );
            ImGui::Text("GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION) );
            ImGui::Text("Vendor: %s", glGetString(GL_VENDOR) );
            ImGui::Text("Renderer: %s", glGetString(GL_RENDERER) );
        ImGui::End();
    }
}