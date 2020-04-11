#include <iostream>
#include <string>

#include "Editor.h"
#include "Constants.h"

// Vertex Array Object (VAO)
// Vertex Buffer Object (VBO)
GLuint VAO, VBO, shader, uniformModel;

bool direction = true;
float triOffset  = 0.0f;
float triMaxoffset = 0.7f;
float triIncrement = 0.005f;

float curlAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

// Vertex Shader
std::string vShader = "                                                \n\
#version 450                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;											  \n\
uniform mat4 model;											                  \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = model * vec4(pos, 1.0);				  \n\
}";

// Fragment Shader
std::string fShader = "                                                \n\
#version 450                                                                  \n\
                                                                              \n\
out vec4 colour;                                                              \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(0.0, 1.0, 0.0, 1.0);                                        \n\
}";

// Our state
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void createTriangle() {
    GLfloat vertices[] {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void addShader(GLuint _program, const char* _shaderCode, GLenum _shaderType) {
    GLuint newShader = glCreateShader(_shaderType);

    const GLchar* shaderCode[1];
    shaderCode[0] = _shaderCode;

    GLint codeLenght[1];
    codeLenght[0] = strlen(_shaderCode);

    glShaderSource(newShader, 1, shaderCode, codeLenght);
    glCompileShader(newShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(newShader, GL_COMPILE_STATUS, &result);

    if ( !result ) {
        glGetShaderInfoLog(shader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error compiling " << _shaderType << " shader: " <<  eLog << std::endl;
        return ;
    }

    glAttachShader(_program, newShader);
}

void compileShader() {
    shader = glCreateProgram();

    if ( !shader ) {
        std::cerr << "Error creating shader program" << std::endl;
        return ;
    }

    addShader(shader, vShader.c_str(), GL_VERTEX_SHADER);
    addShader(shader, fShader.c_str(), GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);

    if ( !result ) {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error linking program: " << eLog << std::endl;
        return ;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

    if ( !result ) {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error validating program: " << eLog << std::endl;
        return ;
    }

    uniformModel = glGetUniformLocation(shader, "model");
}

// Windows bullshit
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "Glfw Error " << error << ": " << description << std::endl;
}

#if __APPLE__
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#endif

Editor::Editor(ImGuiIO& _io) : io(_io), editorIsRunning(true) {  }

Editor::~Editor() = default;

bool Editor::isRunning() { return editorIsRunning; }

void Editor::initialized(const int& _width, const int& _height) {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);

    if ( !glfwInit() ) {
        editorIsRunning = false;
    }

    // GL 4.5 + GLSL 450
    std::string glsl_version = "#version 450";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    window = glfwCreateWindow(_width, _height, "2D Map Editor", nullptr, nullptr);

    if ( !window ) {
        std::cout << "GLFW Window creation failed" << std::endl;
        editorIsRunning = false;
    }

    // This function makes the OpenGL or OpenGL ES context of the specified window current on the calling thread
    glfwMakeContextCurrent(window);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    // Enable vsync
    glfwSwapInterval(1);

    // Initialize OpenGL loader
    if ( glewInit() != GLEW_OK ) {
        std::cout << "GLEW initialisation failed!" << std::endl;
        editorIsRunning = false;
    }

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    // Load Font
    io.Fonts->AddFontFromFileTTF("assets/fonts/Karla-Regular.ttf", 16.0f);

    createTriangle();
    compileShader();
}

void Editor::processInput() {
    // This function processes only those events that are already in the event queue and then returns immediately.
    glfwPollEvents();

    if ( glfwWindowShouldClose(window) ) {
        editorIsRunning = false;
    }
}

void Editor::renderUI() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if ( ImGui::BeginMainMenuBar() ) {
        if ( ImGui::BeginMenu("File") ) {
            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save As..")) {}

            ImGui::Separator();
            if ( ImGui::BeginMenu("Options") )
            {
                static bool enabled = true;
                ImGui::MenuItem("Enabled", "", &enabled);
                ImGui::BeginChild("child", ImVec2(0, 60), true);
                for (int i = 0; i < 10; i++)
                    ImGui::Text("Scrolling Text %d", i);
                ImGui::EndChild();
                static float f = 0.5f;
                static int n = 0;
                ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
                ImGui::InputFloat("Input", &f, 0.1f);
                ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
                ImGui::EndMenu();
            }

            if ( ImGui::MenuItem("Quit", "Alt+F4") ) { editorIsRunning = false; }

            ImGui::EndMenu();
        }

        if ( ImGui::BeginMenu("Edit") ) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    // Create a window called "Hello, world!" and append into it.
    ImGui::Begin("Version of GLFW, GLSL and OpenGL");

    // Display some text (you can use a format strings too)
    // GLFW Version
    ImGui::Text("GLFW version: %d,%d,%d", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION );

    // glGetString returns a pointer to a static string describing some aspect of the current GL connection.
    // Returns the company responsible for this GL implementation. This name does not change from release to release.
    ImGui::Text("OpenGL version: %s", glGetString(GL_VERSION) );

    // Returns a version or release number for the shading language.
    ImGui::Text("GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION) );

    // Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release.
    ImGui::Text("Vendor: %s", glGetString(GL_VENDOR) );

    // Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release.
    ImGui::Text("Renderer: %s", glGetString(GL_RENDERER) );

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

void Editor::render() {
    if ( direction ) {
        triOffset += triIncrement;
    } else {
        triOffset -= triIncrement;
    }

    if ( std::abs(triOffset) >= triMaxoffset ) {
        direction = !direction;
    }

    curlAngle = curlAngle <= 360 ? curlAngle + 0.1f : curlAngle - 360;

    if ( sizeDirection ) {
        curSize += 0.001f;
    } else {
        curSize -= 0.001f;
    }

    if ( curSize >= maxSize || curSize <= minSize ) {
        sizeDirection = !sizeDirection;
    }

    renderUI();

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

    glUseProgram(shader);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
//    model = glm::rotate(model, curlAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(curSize, curSize, 1.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glUseProgram(0);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // This function swaps the front and back buffers of the specified window.
    glfwSwapBuffers(window);
}

void Editor::destroy() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // This function destroys the specified window and its context.
    glfwDestroyWindow(window);

    // This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any other allocated resources.
    glfwTerminate();
}