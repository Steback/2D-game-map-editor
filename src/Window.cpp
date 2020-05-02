#include <iostream>

#include "Window.h"

bool Window::editorIsRunning;

Window::Window(const int &_width, const int &_height) : windowSize(glm::vec2(_width, _height)) {  }

Window::~Window() = default;

void Window::initialized() {
    if ( !glfwInit() ) {
        std::cerr << "Error Initialising GLFW" << std::endl;
        editorIsRunning = false;
    }

    // GL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
    window = glfwCreateWindow(windowSize.x, windowSize.y, "2D Map Editor", nullptr, nullptr);

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

    windowColor = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
    editorIsRunning = true;
}

bool Window::isRunning() { return editorIsRunning; }

void Window::processInput() {
    // This function processes only those events that are already in the event queue and then returns immediately.
    glfwPollEvents();

    if ( glfwWindowShouldClose(window) ) {
        editorIsRunning = false;
    }
}

void Window::swapBuffers() { glfwSwapBuffers(window); }

void Window::render() {
    // This function retrieves the size, in pixels, of the framebuffer of the specified window.
    glfwGetFramebufferSize(window, &bufferWidth, &buffetHeight);

    // glViewport specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
    glViewport(0, 0, bufferWidth, buffetHeight);

    // glClearColor specifies the red, green, blue, and alpha values used by glClear to clear the color buffers.
    glClearColor(windowColor.x, windowColor.y, windowColor.z, windowColor.w);

    // glClear sets the bitplane area of the window to values previously selected by glClearColor, glClearIndex, glClearDepth, glClearStencil, and glClearAccum.
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::destroy() {
    // This function destroys the specified window and its context.
    glfwDestroyWindow(window);

    // This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any other allocated resources.
    glfwTerminate();
}