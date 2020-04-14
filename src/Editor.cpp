#include <iostream>
#include <string>

#include "Editor.h"
#include "EditorUI.h"

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "Glfw Error " << error << ": " << description << std::endl;
}

Editor::Editor(ImGuiIO& _io) : io(_io) {  }

Editor::~Editor() = default;

bool Editor::editorIsRunning = true;

bool Editor::isRunning() { return editorIsRunning; }

void Editor::initialized(const int& _width, const int& _height) {
    glfwSetErrorCallback(glfw_error_callback);

    if ( !glfwInit() ) {
        editorIsRunning = false;
    }

    // GL 4.5 + GLSL 450
    std::string glsl_version = "#version 450";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Windows bullshit
    #if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
        #pragma comment(lib, "legacy_stdio_definitions")
    #endif

    // Required on Mac
    #if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create window with graphics context
    window = glfwCreateWindow(_width, _height, "2D Map Editor", nullptr, nullptr);

    if ( !window ) {
        std::cout << "GLFW Window creation failed" << std::endl;
        editorIsRunning = false;
    }

    // This function makes the OpenGL or OpenGL ES context of the specified window current on the calling thread
    glfwMakeContextCurrent(window);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    // Enable vsync
    glfwSwapInterval(1);

    // Initialize OpenGL loader
    if ( glewInit() != GLEW_OK ) {
        std::cout << "GLEW initialisation failed!" << std::endl;
        editorIsRunning = false;
    }

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    // Load Font
    io.Fonts->AddFontFromFileTTF("assets/fonts/Karla-Regular.ttf", 16.0f);
}

void Editor::processInput() {
    // This function processes only those events that are already in the event queue and then returns immediately.
    glfwPollEvents();

    if ( glfwWindowShouldClose(window) ) {
        editorIsRunning = false;
    }
}

void Editor::renderUI() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    EditorUI::mainMenuBar();
    EditorUI::assetsPanel(io.DisplaySize.x, io.DisplaySize.y);
    EditorUI::statsPanel(io.DisplaySize.x, io.DisplaySize.y);

    // Rendering
    ImGui::Render();
}

void Editor::render() {
    renderUI();

    // This function retrieves the size, in pixels, of the framebuffer of the specified window.
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);

    // glViewport specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
    glViewport(0, 0, displayWidth, displayHeight);

    // glClearColor specifies the red, green, blue, and alpha values used by glClear to clear the color buffers.
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);

    // glClear sets the bitplane area of the window to values previously selected by glClearColor, glClearIndex, glClearDepth, glClearStencil, and glClearAccum.
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // This function swaps the front and back buffers of the specified window.
    glfwSwapBuffers(window);
}

void Editor::destroy() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // This function destroys the specified window and its context.
    glfwDestroyWindow(window);

    // This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any other allocated resources.
    glfwTerminate();
}