#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui_impl_sdl.h"
#include "../lib/imgui/imgui_impl_opengl3.h"

// Function to define the GLSL versions
std::string setGLSLVersion() {
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
        // GL 4.5 + GLSL 450
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

int main(int, const char**) {
    // Bool variable to define if loop run or not
    bool isRunnig = true;

    // Call function for define de GL version
    std::string glsl_version = setGLSLVersion();

    // Use this function to initialize the SDL library. This must be called before using most other SDL functions.
    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        isRunnig = false;
    }

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Window flags for SDL window
    auto window_flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    // Use this function to create a window with the specified position, dimensions, and flags.
    SDL_Window* window = SDL_CreateWindow(
            "Game Map Editor",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1280,
            720,
            window_flags
    );

    if ( !window ) {
        std::cerr << "Error creating SDL window." << std::endl;
        isRunnig = false;
    }

    // CUse this function to create an OpenGL context for use with an OpenGL window, and make it current.
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    // Use this function to set up an OpenGL context for rendering into an OpenGL window.
    SDL_GL_MakeCurrent(window, gl_context);

    // Use this function to set an OpenGL window attribute before window creation.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Enable vsync
    SDL_GL_SetSwapInterval(1);

    // Initializing GLEW
    if( glewInit() != GLEW_OK ) {
        std::cerr << "Failed to initialize OpenGL loader: " << glewGetErrorString( glewInit() ) << std::endl;
        isRunnig = false;
    }

    // A structure that contains information about the version of SDL in use.
    SDL_version compiled;
    SDL_version linked;

    // Use this macro to determine the SDL version your program was compiled against.
    SDL_VERSION(&compiled);

    // Use this function to get the version of SDL that is linked against your program.
    SDL_GetVersion(&linked);

    fprintf(stdout, "SDL version: %d.%d.%d \n",compiled.major, compiled.minor, compiled.patch);

    // glGetString returns a pointer to a static string describing some aspect of the current GL connection.
    // Returns the company responsible for this GL implementation. This name does not change from release to release.
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // Returns a version or release number for the shading language.
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release.
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;

    // Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release.
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // glEnable and glDisable enable and disable various capabilities.
    // GL_TEXTURE_2D: If enabled and no fragment shader is active, two-dimensional texturing is performed
    glEnable(GL_TEXTURE_2D);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    // Initiallise Dear ImGui
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    ImGui::StyleColorsDark();

    // Our state
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while ( isRunnig ) {
        // A union that contains structures for the different event types.
        SDL_Event event;

        // Use this function to poll for currently pending events.
        SDL_PollEvent(&event);

        ImGui_ImplSDL2_ProcessEvent(&event);

        if ( event.type == SDL_QUIT ) {
            isRunnig = false;
        }

        if ( event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window) ) {
            isRunnig = false;
        }

        if ( event.type == SDL_KEYDOWN ) {
            if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                isRunnig = false;
            }
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        static float f = 0.0f;
        static int counter = 0;

        // Create a window called "Hello, world!" and append into it.
        ImGui::Begin("Hello, world!");

        // Display some text (you can use a format strings too)
        ImGui::Text("This is some useful text.");

        // Edit bools storing our window open/close state
        ImGui::Checkbox("Demo Window", &show_demo_window);

        // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

        // Edit 3 floats representing a color
        ImGui::ColorEdit3("clear color", (float*)&clear_color);

        // Buttons return true when clicked (most widgets return true when edited/activated)
        if ( ImGui::Button("Button") ) {
            counter++;
        }

        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        // Rendering
        ImGui::Render();

        // glViewport specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
        glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));

        // glClearColor specifies the red, green, blue, and alpha values used by glClear to clear the color buffers.
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        // lClear sets the bitplane area of the window to values previously selected by glClearColor, glClearIndex, glClearDepth, glClearStencil, and glClearAccum.
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Use this function to update a window with OpenGL rendering.
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Use this function to create an OpenGL context for use with an OpenGL window, and make it current.
    SDL_GL_DeleteContext(gl_context);

    // Use this function to destroy a window.
    SDL_DestroyWindow(window);

    // Use this function to clean up all initialized subsystems. You should call it upon all exit conditions.
    SDL_Quit();

    return 0;
}