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

    Window window (WINDOW_WIDTH, WINDOW_HEIGHT);
    EditorUI ui(io);

    window.initialized();
    ui.initialized(window.getWindow());

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
    Camera camera(90.0f, window.getWindowSize().x, window.getWindowSize().y, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 20.0f));

    GLuint  uniformModel = 0, uniformProjection = 0, uniformView = 0;

    // Main loop
    while ( !window.isRunning() ) {
        // This function processes only those events that are already in the event queue and then returns immediately.
        glfwPollEvents();

        window.render();
        ui.renderUI();

        shader.UseShader();

        uniformModel = shader.GetUniformLocation("model");
        uniformProjection = shader.GetUniformLocation("projection");
        uniformView = shader.GetUniformLocation("view");

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.5f, 2.5f, 0.0f));
        model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(camera.getprojectionMatrix()));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
        mesh.RenderMesh();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.swapBuffers();
    }

    window.destroy();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}