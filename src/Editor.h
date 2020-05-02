#ifndef EDITOR_H
#define EDITOR_H

// Dear ImGui
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui_impl_glfw.h"
#include "../lib/imgui/imgui_impl_opengl3.h"

// OpenGL loader
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

class AssetsManager;
class EntityManager;

class Editor {
    public:
        Editor();
        ~Editor();

    private:

};

#endif