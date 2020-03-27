#include <iostream>
#include "Editor.h"
#include "Constants.h"

Editor::Editor(ImGuiIO& _io) : editorIsRunning(true), io(_io) {  }

Editor::~Editor() = default;

bool Editor::isRunning() const { return editorIsRunning; }

void Editor::getData() {
    SDL_version compiled;
    SDL_version linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    fprintf(stdout, "SDL version: %d.%d.%d \n",compiled.major, compiled.minor, compiled.patch);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

std::string Editor::setGLSLVersion() {
    // Decide GL+GLSL versions
    #if __APPLE__
        // GL 3.2 Core + GLSL 150
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        return "#version 150";
    #else
    #ifdef __LINUX__
        // GL 4.5 + GLSL 450, adapt to your case
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

        return "#version 450";
    #else
        // GL 3.0 + GLSL 130
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        return "#version 130";
    #endif
    #endif
}

void Editor::initialize(const int &_width, const int &_height) {
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0 ) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        editorIsRunning = false;
    }

    auto window_flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    window = SDL_CreateWindow(
            "Game Map Editor",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _width,
            _height,
            window_flags
    );

    glsl_version = setGLSLVersion();

    if ( !window ) {
        std::cerr << "Error creating SDL window." << std::endl;
        editorIsRunning = false;
    }

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    auto gl = glewInit();

    if( gl != 0) {
        std::cerr << "Failed to initialize OpenGL loader: " << glewGetErrorString(gl) << std::endl;
        editorIsRunning = false;
    }

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    getData();
}

void Editor::processInput() {
    SDL_PollEvent(&event);

    ImGui_ImplSDL2_ProcessEvent(&event);

    if ( event.type == SDL_QUIT ) {
        editorIsRunning = false;
    }

    if ( event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window) ) {
        editorIsRunning = false;
    }

    if ( event.type == SDL_KEYDOWN ) {
        if ( event.key.keysym.sym == SDLK_ESCAPE ) {
            editorIsRunning = false;
        }
    }
}

void Editor::render() {

}

void Editor::renderUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    // render your GUI
    ImGui::Begin("Demo window");
    ImGui::Button("Hello!");
    ImGui::End();

    ImGui::Render();

    glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}

void Editor::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}