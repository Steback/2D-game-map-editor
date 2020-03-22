#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Editor {
    public:
        Editor();
        ~Editor();
        bool isRunning() const;
        void initialize(const int& _width, const int& _height);
        void processInput();
        void update();
        void render();
        void destroy();

    public:
        int ticksLastFrame{};

    private:
        bool editorIsRunning;
        SDL_Window* window{};
        SDL_Renderer* renderer{};
        SDL_Event event;
};

#endif