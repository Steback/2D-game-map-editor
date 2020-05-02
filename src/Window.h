#ifndef WINDOW_H
#define WINDOW_H

// OpenGL loader
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#include "../lib/glm/glm.hpp"

class Window {
    public:
        Window(const int& _width, const int& _height);
        ~Window();
        void initialized();
        static bool isRunning();
        void processInput();
        void swapBuffers();
        void render();
        void destroy();

        GLFWwindow* window{};

    private:
        static bool editorIsRunning;
        glm::vec2 windowSize;
        int bufferWidth{}, buffetHeight{};
        glm::vec4 windowColor{};
};

#endif
