#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui_impl_sdl.h"
#include "../lib/imgui/imgui_impl_opengl3.h"
#include <string>

class Editor {
    public:
        explicit Editor(ImGuiIO& _io);
        ~Editor();
        bool isRunning() const;
        static void getData();
        static std::string setGLSLVersion();
        void initialize(const int& _width, const int& _height);
        void processInput();
        void render();
        void renderUI();
        void destroy();

    public:
        std::string glsl_version;

    private:
        bool editorIsRunning;
        SDL_Window* window{};
        SDL_Event event{};
        SDL_GLContext gl_context{};
        ImGuiIO& io;
        ImVec4 clear_color;
};

#endif