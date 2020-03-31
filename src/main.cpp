#include "../lib//imgui/imgui.h"
#include "../lib/imgui_glfw/imgui_impl_glfw.h"
#include "../lib//imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <string>

// OpenGL loader
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// Windows bullshit
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "Glfw Error " << error << ": " << description << std::endl;
}

int main(int, char**) {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#endif

    // GL 4.5 + GLSL 450
    std::string glsl_version = "#version 450";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);

    if (window == nullptr) {
        return 1;
    }

    // This function makes the OpenGL or OpenGL ES context of the specified window current on the calling thread
    glfwMakeContextCurrent(window);

    // Enable vsync
    glfwSwapInterval(1);

    // Initialize OpenGL loader
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize OpenGL loader!" << std::endl;
        return 1;
    }

    // GLFW Version
    std::cout <<  "GLFW version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;

    // glGetString returns a pointer to a static string describing some aspect of the current GL connection.
    // Returns the company responsible for this GL implementation. This name does not change from release to release.
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // Returns a version or release number for the shading language.
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release.
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;

    // Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release.
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    // Load Font
    io.Fonts->AddFontFromFileTTF("assets/fonts/Karla-Regular.ttf", 16.0f);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while ( !glfwWindowShouldClose(window) ) {

        // This function processes only those events that are already in the event queue and then returns immediately.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if ( show_demo_window ) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        static float f = 0.0f;
        static int counter = 0;

        // Create a window called "Hello, world!" and append into it.
        ImGui::Begin("Hello, world!");

        // Display some text (you can use a format strings too)
        ImGui::Text("This is some useful text.");

        // Edit bools storing our window open/close state
        ImGui::Checkbox("Demo Window", &show_demo_window);
        ImGui::Checkbox("Another Window", &show_another_window);

        // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

        // Edit 3 floats representing a color
        ImGui::ColorEdit3("clear color", (float*)&clear_color);

        // Buttons return true when clicked (most widgets return true when edited/activated)
        if ( ImGui::Button("Button") )     {
            counter++;
        }

        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("GLFW version: %d,%d,%d", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION );
        ImGui::Text("OpenGL version: %s", glGetString(GL_VERSION) );
        ImGui::Text("GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION) );
        ImGui::Text("Vendor: %s", glGetString(GL_VENDOR) );
        ImGui::Text("Renderer: %s", glGetString(GL_RENDERER) );

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        if ( show_another_window ) {
            // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");

            if ( ImGui::Button("Close Me") ) {
                show_another_window = false;
            }

            ImGui::End();
        }

        // Rendering
        ImGui::Render();

        int display_w, display_h;

        // This function retrieves the size, in pixels, of the framebuffer of the specified window.
        glfwGetFramebufferSize(window, &display_w, &display_h);

        // glViewport specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
        glViewport(0, 0, display_w, display_h);

        // glClearColor specifies the red, green, blue, and alpha values used by glClear to clear the color buffers.
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        // glClear sets the bitplane area of the window to values previously selected by glClearColor, glClearIndex, glClearDepth, glClearStencil, and glClearAccum.
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // This function swaps the front and back buffers of the specified window.
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // This function destroys the specified window and its context.
    glfwDestroyWindow(window);

    // This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any other allocated resources.
    glfwTerminate();

    return 0;
}