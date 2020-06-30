#include <iostream>

#include "Window.h"

Window::Window() : windowSize(glm::vec2(1280, 720)) {  }

Window::Window(const int &_width, const int &_height) : windowSize(glm::vec2(_width, _height)) {  }

Window::~Window() = default;

void Window::initialized() {
    if ( !glfwInit() ) {
        std::cerr << "Error Initialising GLFW" << std::endl;
        return ;
    }

    // GL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    window = glfwCreateWindow(windowSize.x, windowSize.y, "2D Map Editor", nullptr, nullptr);

    if ( !window ) {
        std::cout << "GLFW Window creation failed" << std::endl;
        return ;
    }

    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    glfwSwapInterval(1);

    if ( glewInit() != GLEW_OK ) {
        std::cout << "GLEW initialisation failed!" << std::endl;
        return ;
    }

    windowColor = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
}

bool Window::isRunning() const { return glfwWindowShouldClose(window); }

void Window::swapBuffers() const { glfwSwapBuffers(window); }

void Window::render() {
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    glViewport(0, 0, bufferWidth, bufferHeight);
    glClearColor(windowColor.x, windowColor.y, windowColor.z, windowColor.w);

    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::destroy() const {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow * Window::getWindow() { return window; }

glm::vec2 Window::getWindowSize() { return windowSize; }
