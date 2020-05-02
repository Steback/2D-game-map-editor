#include <vector>

#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"

#include "Constants.h"
#include "Window.h"
#include "EditorUI.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

int main(int, char**) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    auto* window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);
    EditorUI ui(io);

    window->initialized();
    ui.initialized(window->window);

    std::vector<Shape> vertices {
            { -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f,},
            { -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, },
            { 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, },
            { 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    };

    std::vector<GLuint> indices{
            0, 1, 2,
            0, 2, 3
    };

    Shader shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
    Mesh mesh(vertices, indices);
    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

    GLuint  uniformModel = 0, uniformProjection = 0, uniformView = 0;

    // Main loop
    while ( Window::isRunning() ) {
        window->processInput();
        window->render();
        ui.renderUI();

        shader.UseShader();

        uniformModel = shader.GetUniformLocation("model");
        uniformProjection = shader.GetUniformLocation("projection");
        uniformView = shader.GetUniformLocation("view");

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.0f));
        model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        mesh.RenderMesh();

        ui.draw();
        window->swapBuffers();
    }

    window->destroy();
    ui.destroy();

    delete window;

    return 0;
}