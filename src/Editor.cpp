#include <iostream>
#include "Editor.h"
#include "Constants.h"

Editor::Editor() : editorIsRunning(true) {  }

Editor::~Editor() = default;

bool Editor::isRunning() const { return editorIsRunning; }

void Editor::initialize(const int &_width, const int &_height) {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        std::cerr << "Error initializing SDL." << std::endl;
        editorIsRunning = false;
    }

    window = SDL_CreateWindow(
            "Game Map Editor",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _width,
            _height,
            0
    );

    if ( !window ) {
        std::cerr << "Error creating SDL window." << std::endl;
        editorIsRunning = false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if ( !renderer ) {
        std::cerr << "Error creating SDL renderer." << std::endl;
    }
}

void Editor::processInput() {
    SDL_PollEvent(&event);

    switch ( event.type ) {
        case SDL_QUIT: {
            editorIsRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                editorIsRunning = false;
            }

            break;
        }
        default: {
            break;
        }
    }
}

void Editor::update() {
    // Wait until 16ms has ellapsed since the last frame
    while ( !SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME) );

    // Delta time is the difference in ticks from last frame converted to seconds
    float deltaTime = ( SDL_GetTicks() - static_cast<float>(ticksLastFrame) ) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();
}

void Editor::render() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rectangle;

    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 100;
    rectangle.h = 100;

    SDL_RenderFillRect(renderer, &rectangle);
}

void Editor::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}