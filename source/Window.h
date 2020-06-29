#ifndef WINDOW_H
#define WINDOW_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

class Window {
    public:
        Window();
        Window(const int& _width, const int& _height);
        ~Window();
        void initialized();
        bool isRunning() const;
        void swapBuffers() const;
        void render();
        void destroy() const;
        GLFWwindow* getWindow();
        glm::vec2 getWindowSize();

    private:
        GLFWwindow* window{};
        glm::vec2 windowSize;
        int bufferWidth{}, bufferHeight{};
        glm::vec4 windowColor{};

        static void mousePosition(GLFWwindow* window, double x, double y);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif
