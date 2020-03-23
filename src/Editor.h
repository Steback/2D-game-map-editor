#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui_impl_sdl.h"
#include "../lib/imgui/imgui_impl_opengl3.h"

class Editor {
    public:
        Editor(ImGuiIO& _io);
        ~Editor();
        bool isRunning() const;
        void initialize(const int& _width, const int& _height);
        void processInput();
        void update();
        void render();
        void destroy();

    private:
        bool editorIsRunning;
        SDL_Window* window{};
        SDL_Event event{};
        ImGuiIO& io;
        SDL_GLContext gl_context{};
        bool show_demo_window{};
        bool show_another_window{};
        ImVec4 clear_color;
        float f{};
        int counter{};
};

#endif