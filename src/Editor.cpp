#include <iostream>
#include <string>

#include "Editor.h"
#include "Constants.h"

// Our state
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

// Windows bullshit
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "Glfw Error " << error << ": " << description << std::endl;
}

#if __APPLE__
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#endif

Editor::Editor(ImGuiIO& _io) : io(_io), editorIsRunning(true) {  }

Editor::~Editor() = default;

bool Editor::isRunning() { return editorIsRunning; }

void Editor::initialized(const int& _width, const int& _height) {
    // Setup window
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

bool showInfo = false;

void Editor::renderUI() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Menu bar
    if ( ImGui::BeginMainMenuBar() ) {
        if ( ImGui::BeginMenu("File") ) {
            if ( ImGui::MenuItem("New") ) {  }
            if ( ImGui::MenuItem("Open", "Ctrl+O") ) {  }
            if ( ImGui::MenuItem("Save", "Ctrl+S") ) {  }
            if ( ImGui::MenuItem("Save As..") ) { }

            ImGui::Separator();

            if ( ImGui::MenuItem("Options") ) { showInfo = !showInfo; }

            if ( ImGui::MenuItem("Quit", "Alt+F4") ) { editorIsRunning = false; }

            ImGui::EndMenu();
        }

        if ( ImGui::BeginMenu("Edit") ) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    getInfo(showInfo);
}

void Editor::render() {
    renderUI();

    // Rendering
    ImGui::Render();

    int display_w, display_h;

    // This function retrieves the size, in pixels, of the framebuffer of the specified window.
    glfwGetFramebufferSize(window, &display_w, &display_h);

    // glViewport specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
    glViewport(0, 0, display_w, display_h);

    // glClearColor specifies the red, green, blue, and alpha values used by glClear to clear the color buffers.
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

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

void Editor::getInfo(const bool& _open) {
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